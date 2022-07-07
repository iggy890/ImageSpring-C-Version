#include <Cocoa/Cocoa.h>

@interface window:NSObject {
    NSWindow *window = [[NSWindow alloc] init];
    void init() {
        
    }
    
    void setColor(NSColor color) {
        [window setBackgroundColor:[NSColor color]];
    }
    
    void size(int width, int height) {
        
    }
    void mainloop() {
        
    }
}
@end

int main() {
@autoreleasepool {
        // Create a default window
        NSWindow *window = [[NSWindow alloc] init];
        window.title = @"Test???";
        window.subtitle = @"Bottom Text";
        [window setFrame:NSMakeRect(0.f, 0.f, 300.f, 300.f) display:YES animate:YES];
        // Make it blue just for better visibility
        [window setBackgroundColor:[NSColor blueColor]];
        // Bring to front and make it key
        [window makeKeyAndOrderFront:nil];
        while (1) {
            NSEvent* event = [window nextEventMatchingMask:NSEventMaskAny]; //window shows now
        }
    }
}
