#include <Cocoa/Cocoa.h>

/*
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
*/

NSColor *createColor(float r, float g, float b, float a=0) {
    return [NSColor colorWithCalibratedRed:r green:g blue:b alpha:a];
}

NSRect createRect(float startX, float startY, float width, float height) {
    return NSMakeRect(startX, startY, width, height);
}

int main() {
@autoreleasepool {
        // Create a default window
        NSWindow *window = [[NSWindow alloc] init];
        window.title = @"Title";
        window.subtitle = @"Subtitle";

        NSRect *pos = createRect(10, 10, 20, 20);
        NSTextField *yourLabel = [[NSTextField alloc] initWithFrame:pos];

        [window setFrame:createRect(0, 0, 300, 300) display:YES animate:YES];

        [window setBackgroundColor: createColor(0.5, 1, 0.1)];
        [window makeKeyAndOrderFront:nil];

        while (1) {
            NSEvent *event = [window nextEventMatchingMask:NSEventMaskAny];
        }
    }
}
