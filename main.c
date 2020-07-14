#include <SDL2/SDL.h>

SDL_Event e;
SDL_Window *window;
SDL_Renderer *renderer;
SDL_Rect r = {100, 100, 100, 100};
SDL_Texture *iconTexture;
SDL_Surface *s1;
SDL_Surface *s2;

static int test() {
    int sx = 1;
    int sy = 1;
    
    while(1) {
        int wx ,wy = 0;
        SDL_GetWindowSize(window, &wx, &wy);
        if((r.x + r.w + sx >= wx && sx > 0) || (r.x - sx <= 0 && sx < 0)) {
            sx = -sx;
        }
        if((r.y + r.h + sy >= wy && sy > 0) || (r.y - sy <= 0 && sy < 0)) {
            sy = -sy;
        }
        r.x += sx;
        r.y += sy;
        SDL_Delay(10);
    }
    return 0;
}

int main(int argc, char **argv) {
    SDL_Init(SDL_INIT_AUDIO);
    window = SDL_CreateWindow("test",SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, 600, 600, SDL_WINDOW_RESIZABLE
    );
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    s1 = SDL_LoadBMP("icon.bmp");
    s2 = SDL_LoadBMP("sagiri.bmp");
    iconTexture = SDL_CreateTextureFromSurface(renderer, s1);
    SDL_SetTextureColorMod(iconTexture, 0xff, 0xff, 0xff);
    
    //SDL_SetWindowSize(window, 1920, 1080);
    //SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
    SDL_SetWindowIcon(window, s1);
    SDL_Thread *t = SDL_CreateThread(test, "test", NULL);
    
    // 图标位置
    SDL_Rect s = {0, 0, 100, 100};
    while(e.type != SDL_QUIT) {
        SDL_PollEvent(&e);
        
        // 鼠标按下事件
        if(e.type == SDL_MOUSEBUTTONDOWN) {
            // 鼠标左键
            if(e.button.button == SDL_BUTTON_LEFT) {
                r.x = e.button.x - r.w/2;
                r.y = e.button.y - r.h/2;
            }
        }
        
        //键盘按下事件
        if(e.type == SDL_KEYDOWN) {
            if(e.key.keysym.sym == SDLK_w) {
                s.y -= 10;
            }
            if(e.key.keysym.sym == SDLK_s) {
                s.y += 10;
            }
            if(e.key.keysym.sym == SDLK_a) {
                s.x  -= 10;
            }
            if(e.key.keysym.sym == SDLK_d) {
                s.x += 10;
            }
        }
        
        SDL_RenderClear(renderer);
        
        // 画一些奇怪的线
        int c = 6;
        SDL_SetRenderDrawColor(renderer, 0xff, 0x00, 0x00, 0x00);
        int ww ,wh = 0;
        SDL_GetWindowSize(window, &ww, &wh);
        int w = ww / c;
        int h = wh / c;
        // 纵
        for(int i = 1; i < c; i ++) {
                SDL_RenderDrawLine(renderer, i*w, 0, i*w, wh);
        }
        // 横
        for(int i = 1; i < c; i ++) {
            SDL_RenderDrawLine(renderer, 0, i*h, ww, i*h);
        }
        // 图标
        SDL_RenderCopy(renderer, iconTexture, NULL, &s);
        
        // 运动的矩形
        SDL_SetRenderDrawColor(renderer, 0x00, 0xff, 0xff, 0x00);
        SDL_RenderFillRect(renderer, &r);
        
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderPresent(renderer);
    }
    
    SDL_DetachThread(t);
    SDL_FreeSurface(s1);
    SDL_FreeSurface(s2);
    SDL_DestroyTexture(iconTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
