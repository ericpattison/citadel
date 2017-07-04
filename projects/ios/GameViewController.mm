#import "GameViewController.h"
#import <OpenGLES/ES3/glext.h>

@interface GameViewController () {}
@property (strong, nonatomic) EAGLContext* context;

- (void) setupGL;
- (void) teardownGL;

@end

@implementation GameViewController

- (void) viewDidLoad {
    [super viewDidLoad];
    
    self.context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES3];
    if(!self.context) {
        NSLog(@"Failed to create OpenGL ES context.");
    }
    
    GLKView* view = (GLKView*)self.view;
    view.context = self.context;
    view.drawableDepthFormat = GLKViewDrawableDepthFormat24;
    
    [self setupGL];
}

- (void) dealloc {
    [self teardownGL];
    
    if([EAGLContext currentContext] == self.context) {
        [EAGLContext setCurrentContext: nil];
    }
}

- (void) didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    if([self isViewLoaded] && ([[self view] window] == nil)) {
        self.view = nil;
        [self teardownGL];
        
        if([EAGLContext currentContext] == self.context) {
            [EAGLContext setCurrentContext: nil];
        }
        self.context = nil;
    }
}

- (BOOL) prefersStatusBarHidden {
    return YES;
}

- (void) setupGL {
    [EAGLContext setCurrentContext:self.context];
}

-(void) teardownGL {
    [EAGLContext setCurrentContext: self.context];
}

- (void) update {
    
}

- (void) glkView:(GLKView *)view drawInRect:(CGRect)rect {
    
}

@end
