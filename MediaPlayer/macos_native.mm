// macos_native.mm
#import <AppKit/AppKit.h>

void setWindowTitleBlur(QWindow *window, bool enabled) {
    NSView* view = (NSView*)window->winId();
    NSWindow* nswindow = [view window];
    [nswindow setTitlebarAppearsTransparent:enabled];
}
