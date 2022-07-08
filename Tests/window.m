#include <Cocoa/Cocoa.h>
#include <stdio.h>

NSColor *createColor(float r, float g, float b, float a) {
    return [NSColor colorWithCalibratedRed:r green:g blue:b alpha:a];
}

NSRect createRect(float startX, float startY, float width, float height) {
    return NSMakeRect(startX, startY, width, height);
}

int main() { @autoreleasepool {
        NSWindow *window = [[NSWindow alloc] init];
        window.title = @"Title";
        window.subtitle = @"Subtitle";

        NSText *t = [[NSText alloc] initWithFrame: createRect(50, 100, 100, 10)];
        t.string = @"hello :)";
        [window.contentView addSubview: t];

        [window setFrame: createRect(0, 0, 200, 200) display:YES animate:YES];
        [window setBackgroundColor: createColor(0.5, 1, 0.1, 1)];
        [window makeKeyAndOrderFront: window];
        
        int p = 0;
        while (1) {
            NSEvent *event = [window nextEventMatchingMask: NSEventMaskAny];
         }
    }
}