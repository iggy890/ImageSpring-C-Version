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

        NSText *t = [[NSText alloc] initWithFrame: createRect(75, 100, 75, 10)];
        t.string = @"Name:";
        [window.contentView addSubview: t];
        
        NSTextField *a = [[NSTextField alloc] initWithFrame: createRect(75, 75, 50, 10)];
        [window.contentView addSubview: a];

        [window setFrame: createRect(0, 0, 200, 200) display:YES animate:YES];
        [window setBackgroundColor: createColor(0.5, 1, 0.1, 1)];
        [window makeKeyAndOrderFront: window];

        while (1) {
            NSEvent *event = [window nextEventMatchingMask: NSEventMaskAny];
            if ([event type] == NSEventTypeRightMouseDown) {
                break;
            }
        }
    }
}