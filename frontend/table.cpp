#include "table.h"

using namespace std;


void Table::init_sdl(){
    this->win_ptr = nullptr;
    this->win_ren = nullptr;

    // start up sdl
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        cout << "Error: SDL Could Not Initialize: " << SDL_GetError() << endl;
        exit(2);
    };
    this->win_ptr = SDL_CreateWindow("Chess", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (this->win_ptr == nullptr){
        cout << "Error: SDL Could Not Create Window: " << SDL_GetError() << endl;
        exit(2);
    }
    this->win_ren = SDL_CreateRenderer(this->win_ptr, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (this->win_ren == nullptr){
        cout << "Error: SDL Couldn't create Renderer: " << SDL_GetError() << endl;
        exit(2);
    }

    SDL_SetRenderDrawBlendMode(this->win_ren, SDL_BLENDMODE_BLEND);
}


Table::Table(chess::TEAM t, chess::GameControl* Game): playerTurn(t), CHESS_GAME(Game){
    init_sdl();
    init_chess_images();
    drawLoop();
}


Table::~Table(){;
    exit_sdl();
}

void Table::exit_sdl(){
    // Unload Textures    
    for (auto i : this->chessImages){
        SDL_DestroyTexture(i.second[chess::WHITE]);
        SDL_DestroyTexture(i.second[chess::BLACK]);
    }
    SDL_DestroyRenderer(this->win_ren);
    SDL_DestroyWindow(this->win_ptr);
    SDL_Quit();
}

void Table::init_chess_images(){
    using namespace chess;
    
    /*Dear God: Why does SDL only natively support bitmap?*/


    // Hash-Table which stores each side's variant image data by the piece_type.
    // The associated team index refers to the image of the respective pair.

    // So chessImages[PAWN][WHITE] will return the white pawn
    // whereas chessImages[KING][BLACK] will return the black king.
    this->chessImages[PAWN] = {load_image("./frontend/images/white_pawn.bmp"), load_image("./frontend/images/black_pawn.bmp")};
    this->chessImages[BISHOP] = {load_image("./frontend/images/white_bishop.bmp"), load_image("./frontend/images/black_bishop.bmp")};
    this->chessImages[KNIGHT] = {load_image("./frontend/images/white_knight.bmp"), load_image("./frontend/images/black_knight.bmp")};
    this->chessImages[ROOK] = {load_image("./frontend/images/white_rook.bmp"), load_image("./frontend/images/black_rook.bmp")};
    this->chessImages[QUEEN] = {load_image("./frontend/images/white_queen.bmp"), load_image("./frontend/images/black_queen.bmp")};
    this->chessImages[KING] = {load_image("./frontend/images/white_king.bmp"), load_image("./frontend/images/black_king.bmp")};

}

SDL_Texture* Table::load_image(string img_path){
    SDL_Surface* surf = SDL_LoadBMP(img_path.c_str());
    if (surf == nullptr){
        cout << "Error could not load .BMP image: " << SDL_GetError() << endl;
        exit(2);
    }

    /*Set Color Key for Transparent Background*/
    SDL_SetColorKey(surf, SDL_TRUE, SDL_MapRGB(surf->format, 255, 0, 0));

    SDL_Texture* text = SDL_CreateTextureFromSurface(this->win_ren, surf);
    if (text == nullptr){
        cout << "Error could not create texture from .BMP image: " << SDL_GetError() << endl;
    }
    SDL_FreeSurface(surf);
    return text;
}

/*Event-Loop for Chess Game*/
void Table::drawLoop(){
    bool running = true;
    // event flag
    SDL_Event e_flag;
    while (running){
        while (SDL_PollEvent(&e_flag)){
            if (e_flag.type == SDL_QUIT){
                running = false;
            }
            if (e_flag.type == SDL_KEYDOWN){
                running = false;
            }
           
            /*Mouse Event Explanation:
                If clicking on an active square in sqr_buffer
                then execute the associated move.  Otherwise
                if clicking on a piece move to the next state
                of having active squares (if the piece has
                possible moves)
            */

            if (e_flag.type == SDL_MOUSEBUTTONDOWN){
                this->handleMouseEvent();
            }
        }
        /*Update Screen Contents!*/
        SDL_RenderClear(this->win_ren);
        this->drawCheckerBoard();
        this->drawMoveBuffer();
        this->drawPieces();
        SDL_RenderPresent(this->win_ren);

    }
}

// transpose mouse coordinates to indices on the matrix
void Table::normalize(int& y, int& x){
    y = (y - (y % (WINDOW_HEIGHT / 8))) / (WINDOW_HEIGHT / 8);
    x = (x - (x % (WINDOW_WIDTH / 8))) / (WINDOW_WIDTH / 8);
}


void Table::drawCheckerBoard(){
    SDL_Rect block;
    block.w = WINDOW_WIDTH / 8;
    block.h = WINDOW_HEIGHT / 8;
    for(block.y = 0; block.y < WINDOW_HEIGHT; block.y += block.h){
        for (block.x = 0; block.x < WINDOW_WIDTH; block.x += block.w){
            swap_render_color();
            SDL_RenderFillRect(this->win_ren, &block);
        }
        swap_render_color();
    }
    return;
}

void Table::swap_render_color(){
    static bool state = true;
    if (state == true){
        SDL_SetRenderDrawColor(this->win_ren, 215, 215, 215, 255);
    } else {
        SDL_SetRenderDrawColor(this->win_ren, 50, 50, 50, 255);
    }
    state = !state;
}

void Table::drawPieces(){
    // Query Pieces from CHESS_GAME
    using namespace chess;
    SDL_Rect dest_rect;
    dest_rect.w = WINDOW_WIDTH / 8;
    dest_rect.h = WINDOW_HEIGHT / 8;
    for (int i=0; i < 8; i++){
        for (int j=0; j < 8; j++){
            Piece_ID pieceHere = CHESS_GAME->query(i, j);
            if (pieceHere.Type != NO_PIECE){
                dest_rect.y = dest_rect.h * i;
                dest_rect.x = dest_rect.w * j;
                SDL_RenderCopy(this->win_ren, chessImages[pieceHere.Type][pieceHere.Side], NULL, &dest_rect);
            }
        }
    }

    return;
}





void Table::handleMouseEvent(){
    int x, y;
    SDL_GetMouseState(&x, &y);
    normalize(x, y);            
    std::array<int, 2> mousePosition = {y, x};
    auto square = move_buffer.find(mousePosition);

    // If no move corresponding move was found then
    // query for new possible moves
    if (square == move_buffer.end()){
        chess::Piece_ID possible_piece = this->CHESS_GAME->query(y, x);
        if (possible_piece.Type != chess::NO_PIECE && possible_piece.Side == playerTurn){
            // clear move buffer
            move_buffer.clear();
            std::vector<chess::Move> newMoves = this->CHESS_GAME->get_legal_moves(y, x);
            for (auto mv : newMoves){
                move_buffer[mv.destination] = mv;
            }
        }
    } else {
        // otherwise execute the move at that location
        this->CHESS_GAME->perform_move(square->second);
        // change player turn
        playerTurn = (playerTurn == chess::WHITE) ? chess::BLACK : chess::WHITE;
        // Then clear the move buffer
        move_buffer.clear();
        /*Check if a side is now in checkmate*/
        if (this->CHESS_GAME->isCheckMate(chess::WHITE)){
            SDL_SetWindowTitle(this->win_ptr, "White has been checkmated!");
        } else if (this->CHESS_GAME->isCheckMate(chess::BLACK)){
            SDL_SetWindowTitle(this->win_ptr, "Black has been checkmated!");
        }
    }
}

void Table::drawMoveBuffer(){
    SDL_SetRenderDrawColor(this->win_ren, 252, 187, 118, 190);
    SDL_Rect active_sqr;
    active_sqr.w = (WINDOW_WIDTH / 8);
    active_sqr.h = (WINDOW_HEIGHT / 8);
    for (auto item : move_buffer){
        active_sqr.y = item.first[0] * active_sqr.h;
        active_sqr.x = item.first[1] * active_sqr.w;
        SDL_RenderFillRect(this->win_ren, &active_sqr);
    }
};