/*!
 * \file s_main_menu.cpp
 *
 * \author FEUP - T03G04:
 * \author Duarte Duarte
 * \author Miguel Marques
 *
 * \date Maio 2012
 * 
 */

#include "s_main_menu.h"
#include "blackjack.h"
#include "card.h"
#include "fonts.h"
#include "rect_button.h"
#include "localization.h"
#include "bitmaps.h"
#include "sounds.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include <vector>

// mouse callback functions
bool ChangeToPlayState(RectButton* btn);
bool ChangeToSettingsState(RectButton* btn);
bool ChangeToQuit(RectButton* btn);

S_MainMenu::S_MainMenu()
{
    _selectedMenu = -1;
}

void S_MainMenu::Initialize()
{
    _selectedMenu = MENU_PLAY;
    
    _playButton = new RectButton(Vector2D(50, 440), al_map_rgb(200, 200, 200), GetStr(STR_PLAY), 50, RectButton::ButtonHandler().Bind<&ChangeToPlayState>(), true);
    _settingButton = new RectButton(Vector2D(50, 441 + 50), al_map_rgb(200, 200, 200), GetStr(STR_OPTIONS), 50, RectButton::ButtonHandler().Bind<&ChangeToSettingsState>(), true);
    _quitButton = new RectButton(Vector2D(50, 441 + 100), al_map_rgb(200, 200, 200), GetStr(STR_QUIT), 50, RectButton::ButtonHandler().Bind<&ChangeToQuit>(), true);
}

void S_MainMenu::LoadContents()
{
    al_reserve_samples(2);

    PlaySoundLoop(SAMPLE_MENU_BACKGROUND_MUSIC);
}

bool S_MainMenu::Update(ALLEGRO_EVENT* ev)
{
    if (!ev)
        return false;

    if (_playButton)
        _playButton->Update(ev);
    if (_settingButton)
        _settingButton->Update(ev);
    if (_quitButton)
        _quitButton->Update(ev);

    switch (ev->type)
    {
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
        {
            return !BlackJack::Instance()->Quit();
        }
        case ALLEGRO_EVENT_KEY_UP:
        {
            if (ev->keyboard.keycode == ALLEGRO_KEY_ESCAPE)
            {
                return !BlackJack::Instance()->Quit(true);
            }
            else if (ev->keyboard.keycode == ALLEGRO_KEY_ENTER)
            {
                if (_selectedMenu == MENU_PLAY)
                {
                    BlackJack::Instance()->ChangeState(STATE_PLAYING);
                    return true;
                }
                else if (_selectedMenu == MENU_SETTINGS)
                {
                    BlackJack::Instance()->ChangeState(STATE_SETTINGS);
                    return true;
                }
                else if (_selectedMenu == MENU_QUIT)
                {
                    BlackJack::Instance()->Quit();
                    return false;
                }
            }
            break;
        }
        case ALLEGRO_EVENT_KEY_DOWN:
        {
            int add;
            if (ev->keyboard.keycode == ALLEGRO_KEY_DOWN)
                add = 1;
            else if (ev->keyboard.keycode == ALLEGRO_KEY_UP)
                add = -1;
            else
                return false;

            // _selectedMenu will always be in the range [0, 2]
            _selectedMenu = (((_selectedMenu + add) == -1) ? MENU_QUIT : ((_selectedMenu + add) % (MENU_QUIT + 1)));

            PlaySoundOnce(SAMPLE_MENU_NEXTM_SOUND);
            return true;
        }
        case ALLEGRO_EVENT_TIMER:
            return true; // draw every 1/60 secs
    }

    return false;
}

void S_MainMenu::Draw()
{
    ALLEGRO_COLOR shadowText = al_map_rgb(0, 0, 0);
    ALLEGRO_COLOR selectedText = al_map_rgb(255, 255, 255);

    static Bitmap bg(BITMAP_MENU_BACKGROUND);
    bg.Draw();

    al_draw_text(Fonts::GetFont(140), shadowText, 267, 1, ALLEGRO_ALIGN_CENTRE, "Blackjack");
    al_draw_text(Fonts::GetFont(140), selectedText, 266, 0, ALLEGRO_ALIGN_CENTRE, "Blackjack");
    
    if (_playButton->IsMouseHovered() && _selectedMenu != MENU_PLAY)
    {
        PlaySoundOnce(SAMPLE_MENU_NEXTM_SOUND);
        _selectedMenu = MENU_PLAY;
    }
    else if (_settingButton->IsMouseHovered() && _selectedMenu != MENU_SETTINGS)
    {
        PlaySoundOnce(SAMPLE_MENU_NEXTM_SOUND);
        _selectedMenu = MENU_SETTINGS;
    }
    else if (_quitButton->IsMouseHovered() && _selectedMenu != MENU_QUIT)
    {
        PlaySoundOnce(SAMPLE_MENU_NEXTM_SOUND);
        _selectedMenu = MENU_QUIT;
    }
    
    bool drawPlay = _selectedMenu == MENU_PLAY;
    bool drawSettings = _selectedMenu == MENU_SETTINGS;
    bool drawQuit = _selectedMenu == MENU_QUIT;

    _playButton->Draw(drawPlay);
    _settingButton->Draw(drawSettings);
    _quitButton->Draw(drawQuit);
}

void S_MainMenu::UnloadContents()
{
    delete _playButton; _playButton = NULL;
    delete _settingButton; _settingButton = NULL;
    delete _quitButton; _quitButton = NULL;
}

bool ChangeToPlayState(RectButton* btn)
{
    BlackJack::Instance()->ChangeState(STATE_PLAYING);
    return true;
}

bool ChangeToSettingsState(RectButton* btn)
{
    BlackJack::Instance()->ChangeState(STATE_SETTINGS);
    return true;
}

bool ChangeToQuit(RectButton* btn)
{
    BlackJack::Instance()->Quit();
    return true;
}
