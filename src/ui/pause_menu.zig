//
// Copyright (C) 2024 The OpenTitus team
//
// Authors:
// Petr Mrázek
//
// "Titus the Fox: To Marrakech and Back" (1992) and
// "Lagaf': Les Aventures de Moktar - Vol 1: La Zoubida" (1991)
// was developed by, and is probably copyrighted by Titus Software,
// which, according to Wikipedia, stopped buisness in 2005.
//
// OpenTitus is not affiliated with Titus Software.
//
// OpenTitus is  free software; you can redistribute  it and/or modify
// it under the  terms of the GNU General  Public License as published
// by the Free  Software Foundation; either version 3  of the License,
// or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful, but
// WITHOUT  ANY  WARRANTY;  without   even  the  implied  warranty  of
// MERCHANTABILITY or  FITNESS FOR A PARTICULAR PURPOSE.   See the GNU
// General Public License for more details.
//

const c = @import("../c.zig");
const SDL = @import("../SDL.zig");

const render = @import("../render.zig");
const window = @import("../window.zig");
const sprites = @import("../sprites.zig");
const fonts = @import("fonts.zig");
const globals = @import("../globals.zig");
const audio = @import("../audio/engine.zig");
const options_menu = @import("options_menu.zig");

const menu = @import("menu.zig");
const MenuAction = menu.MenuAction;
const MenuContext = menu.MenuContext;

fn continueFn(menu_context: *MenuContext) ?c_int {
    _ = menu_context;
    return 0;
}

fn quitFn(menu_context: *MenuContext) ?c_int {
    _ = menu_context;
    return -1;
}

const MenuEntry = struct {
    text: []const u8,
    active: bool,
    handler: *const fn (*MenuContext) ?c_int,
};

const menu_entries: []const MenuEntry = &.{
    .{ .text = "Continue", .active = true, .handler = continueFn },
    .{ .text = "Options", .active = true, .handler = options_menu.optionsMenu },
    .{ .text = "Quit", .active = true, .handler = quitFn },
};

fn renderLabel(font: *fonts.Font, text: []const u8, y: i16, selected: bool) void {
    const options = fonts.Font.RenderOptions{ .transpatent = true };
    const label_width = fonts.Gold.metrics(text, options);
    const x = 160 - label_width / 2;
    if (selected) {
        const left = ">";
        const right = "<";
        const left_width = font.metrics(left, .{});
        font.render(left, x - 4 - left_width, y, .{});
        font.render(right, x + label_width + 4, y, .{});
    }
    font.render_center(text, y, options);
}

fn renderMenu(menu_context: *MenuContext, selected: u8) void {
    menu_context.renderBackground();
    const title_width = fonts.Gold.metrics("PAUSED", .{ .transpatent = true }) + 4;
    var y: i16 = 40;
    fonts.Gold.render_center("PAUSED", y, .{ .transpatent = true });
    y += 12;
    const bar = c.SDL_Rect{ .x = 160 - title_width / 2, .y = y, .w = title_width, .h = 1 };
    _ = c.SDL_FillRect(window.screen.?, &bar, c.SDL_MapRGB(window.screen.?.format, 0xd0, 0xb0, 0x00));
    y += 27;
    for (menu_entries, 0..) |entry, i| {
        renderLabel(if (entry.active) &fonts.Gold else &fonts.Gray, entry.text, y, selected == i);
        y += 14;
    }
    window.window_render();
}

// FIXME: int is really an error enum, see tituserror.h
pub export fn pauseMenu(context: *c.ScreenContext) c_int {

    // take a screenshot and use it as a background that fades to black a bit
    const image = c.SDL_ConvertSurface(window.screen.?, window.screen.?.format, c.SDL_SWSURFACE);
    defer c.SDL_FreeSurface(image);

    defer render.screencontext_reset(context);

    var menu_context: MenuContext = .{
        .background_image = image,
        .background_fade = 0,
    };
    var selected: u8 = 0;
    while (true) {
        const timeout = menu_context.updateBackground();
        SDL.delay(timeout);
        renderMenu(&menu_context, selected);
        audio.music_restart_if_finished();
        var event: c.SDL_Event = undefined;
        while (c.SDL_PollEvent(&event) != 0) { //Check all events
            switch (event.type) {
                c.SDL_QUIT => {
                    return c.TITUS_ERROR_QUIT;
                },
                c.SDL_KEYDOWN => {
                    switch (event.key.keysym.scancode) {
                        c.KEY_ESC => {
                            return 0;
                        },
                        c.KEY_ENTER, c.KEY_RETURN, c.KEY_SPACE => {
                            const ret_val = menu_entries[selected].handler(&menu_context);
                            if (ret_val) |value| {
                                return value;
                            }
                        },
                        c.KEY_FULLSCREEN => {
                            window.toggle_fullscreen();
                        },
                        c.KEY_DOWN => {
                            if (selected < menu_entries.len - 1)
                                selected += 1;
                        },
                        c.KEY_UP => {
                            if (selected > 0)
                                selected -= 1;
                        },
                        c.KEY_M => {
                            _ = audio.music_toggle_c();
                        },
                        else => {
                            // NOOP
                        },
                    }
                },
                else => {
                    // NOOP
                },
            }
        }
    }
}
