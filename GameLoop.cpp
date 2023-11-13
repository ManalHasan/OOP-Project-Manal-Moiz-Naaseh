#include "GameLoop.hpp"

GameLoop::GameLoop() : window(nullptr), renderer(nullptr), GameState(false) {
    p.setSource(0,0,65, 55);
    p.setDest(250,Height/2,65,55);
    ground1.setSource(0, 0, 112, 336);
	ground1.setDest(0, 520, 112, 5);//805
    ground2.setSource(0, 0, 112, 336);//805
	ground2.setDest(0, 520, 112, 5);
    // Pipe_Above1.setSrc(0, 0, 320, 52);
	// Pipe_Above1.setDest(400, -200, 400, 52);
	// Pipe_Below1.setSrc(0, 0, 320, 52);
	// Pipe_Below1.setDest(400, 350, 400, 52);
	// Pipe_Above2.setSrc(0, 0, 320, 52);
	// Pipe_Above2.setDest(700, -200, 400, 52);
	// Pipe_Below2.setSrc(0, 0, 320, 52);
	// Pipe_Below2.setDest(700, 350, 400, 52);
	// Pipe_Above3.setSrc(0, 0, 320, 52);
	// Pipe_Above3.setDest(1000, -200, 400, 52);
	// Pipe_Below3.setSrc(0, 0, 320, 52);
	// Pipe_Below3.setDest(1000, 350, 400, 52);
    
}

bool GameLoop::getGameState(){
    return GameState;
}

void GameLoop::Initialize() {
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow("Flappy Bird", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Width, Height, SDL_WINDOW_RESIZABLE);

    if (window) {
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer) { 
            //if Main menu start game clicked only then do the below so for that getsamestate func in main menu class
            cout << "Succeeded!" << endl;
            GameState= true;
            p.CreateTexture("image/Frame-1 (1).png", renderer);    
            b.CreateTexture("image/bg.png", renderer);
            ground1.CreateTexture("image/base.png", renderer);
			ground2.CreateTexture("image/base.png", renderer);
            b1.CreateTexture("image/brick_3.png", renderer);
            // Pipe_Above1.CreateTexture("image/brick_3.png", renderer);
			// Pipe_Below1.CreateTexture("image/brick_3 (1).png", renderer);
			// Pipe_Above2.CreateTexture("image/brick_3.png", renderer);
			// Pipe_Below2.CreateTexture("image/brick_3 (1).png", renderer);
			// Pipe_Above3.CreateTexture("image/brick_3.png", renderer);
			// Pipe_Below3.CreateTexture("image/brick_3 (1).png", renderer);
        } else {
            cout << "Renderer not created" << endl;
        }
    } else {
        cout << "Window not created" << endl;
    }
}

void GameLoop::MainMenu(){
    menu.Initialize(renderer);
    while (!menu.getClicked()){
        if (menu.EventHandling(event1)==-1){
            GameState=false;
            break;
        }
        //cout<<"I am here";
        SDL_RenderClear(renderer);
		menu.Render(renderer);
		SDL_RenderPresent(renderer);
        
    }
    //sb1.CreateTexture("image/sb.png", renderer);


}

void GameLoop::SelectBird(){
    sb.Initialize(renderer);
    while (!sb.getChosenB()){
        if (sb.EventHandling(event1)==-1){
            GameState = false;
			break;
        }
        SDL_RenderClear(renderer);
		sb.Render(renderer);
		SDL_RenderPresent(renderer);
    }
    //Blue=true;//make a setBlue, Yellow and Owl function, which we can access in the select Bird class, the function will set one of these bool values true and return a number according to whichever bird is true. then in Render function in this class I will set conditions eg: if returned value is 1 p.render()--which will correspond to blue bird, p1 to yellow and p2 to owl 
}

void GameLoop::Event(){
    SDL_PollEvent(&event1);
    if (event1.type==SDL_QUIT){
        GameState=false;
    }
    //Mouse Events
    // if (event1.type==SDL_MOUSEMOTION){
    //     cout<<event1.motion.x<<" "<<event1.motion.y<<endl;
    // }
    // if(event1.type==SDL_MOUSEBUTTONDOWN){
    //     cout<<"Pressed"<<endl;
    // }
    //Keyboard Events
    if (event1.type==SDL_KEYDOWN){
        if (event1.key.keysym.sym==SDLK_UP){//specific to space key
            cout<<"Pressed"<<endl;
            p.Gravity();
        }
    }

}


void GameLoop::Update(){

    b1.Update();
    p.Update();
    ground1.GroundUpdate1();
	ground2.GroundUpdate2();
    score.scoreInc();
    double a=score.getScore();
    score.setHighscore(a);

    CollisionDetection();
}

void GameLoop::CollisionDetection(){
    if (CollisionManager::checkCollision(&p.getDest(), &b1.getDest())){
        GameState=false;//rather than making it end directly, showing end game screen with score on display and options to start again or close
    }
    if (CollisionManager::checkCollision(&p.getDest(), &ground1.getDest())){
        GameState=false;
    }

    if (CollisionManager::checkCollision(&p.getDest(), &ground2.getDest())){
        GameState=false;
    }
}

void GameLoop::Render() {
    SDL_RenderClear(renderer);
    //sb.Render(renderer);
    b.Render(renderer); 
    //pip render
    ground1.GroundRender(renderer);
	ground2.GroundRender(renderer);
    b1.Render(renderer);
    //if (Blue==true){
        p.Render(renderer);
    //}
    SDL_RenderPresent(renderer);
}

void GameLoop::Clear() {
    cout<<score.getScore();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}
