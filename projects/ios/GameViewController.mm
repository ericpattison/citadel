#import "GameViewController.h"
#import <OpenGLES/ES3/glext.h>

#include "../../keep/types.h"
#include "../../keep/constants.h"
#include "../../keep/window/OpenGLWindow.h"
#include "../../castle/game/Game.h"


@interface GameViewController() {}
@property (strong, nonatomic) EAGLContext* context;
@property (nonatomic) OpenGLWindow* window;
@property (nonatomic) SPtr<Device> device;
@property (nonatomic) SPtr<Game> game;

- (void) setupGL;
- (void) tearDownGL;

@end

@implementation GameViewController

-(void) viewDidLoad {
    [super viewDidLoad];
    
    self.context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES3];
    
    if(!self.context) {
        NSLog(@"Failed to create GLES context");
    }
    
    GLKView* view = (GLKView*)self.view;
    view.context = self.context;
    view.drawableDepthFormat = GLKViewDrawableDepthFormat24;
    
    [self setupGL];
    
    struct WindowInfo info;
    self.window = new OpenGLWindow(info);
    self.device = self.window->AcquireDevice();
    self.game = Game::Create(self.device);
}

- (void) dealloc {
    delete self.window;
    [self tearDownGL];
    if([EAGLContext currentContext] == self.context) {
        [EAGLContext setCurrentContext: nil];
    }
}

- (void) didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    if([self isViewLoaded] && [[self view] window] == nil) {
        self.view = nil;
        [self tearDownGL];
        if([EAGLContext currentContext] == self.context) {
            [EAGLContext setCurrentContext: nil];
        }
        self.context = nil;
    }
}

- (BOOL) preferStatusBarHidden {
    return YES;
}

- (void) setupGL {
    [EAGLContext setCurrentContext: self.context];
    
}

- (void) tearDownGL {
    [EAGLContext setCurrentContext: self.context];
}

#pragma mark - GLKView and GLKViewController delegate methods

- (void) update {
    
}

- (void) glkView:(GLKView *)view drawInRect:(CGRect)rect {
    self.device->Clear();
    
    self.				device->Present();
}

@end
