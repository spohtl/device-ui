#ifdef VIEW_320x240

#include "TFTView_320x240.h"
#include <cstdio>
#include <functional>
#include <algorithm>
#include "Arduino.h"
#include "ui.h" // this is the ui generated by lvgl / squareline editor
#include "ViewController.h"

#ifdef USE_X11
#include "X11Driver.h"
#elif defined (LGFX_DRIVER_INC)
#include "LGFXDriver.h"
#include LGFX_DRIVER_INC
#else
#error "Unknown device for view 320x240"
#endif

#define CR_REPLACEMENT 0x0C  // dummy to record several lines in a one line textarea

// children index of nodepanel lv objects (see addNode)
enum NodePanelIdx {
    node_img_idx,
    node_btn_idx,
    node_lbl_idx,
    node_lbs_idx,
    node_bat_idx,
    node_lh_idx,
    node_sig_idx
};

TFTView_320x240* TFTView_320x240::gui = nullptr;

TFTView_320x240* TFTView_320x240::instance(void) {
    if (!gui) gui = new TFTView_320x240;
    return gui;
}

#ifdef USE_X11
TFTView_320x240::TFTView_320x240() : MeshtasticView(&X11Driver::create(), new ViewController) {
}
#else
TFTView_320x240::TFTView_320x240() : MeshtasticView(new LGFXDriver<LGFX_DRIVER>(screenWidth, screenHeight),
                                               new ViewController) {
}
#endif

void TFTView_320x240::init(IClientBase* client) {
    Serial.println("TFTView init...");
    displaydriver->init();
    MeshtasticView::init(client);
    
    ui_set_active(ui_HomeButton, ui_HomePanel, ui_TopPanel);
    ui_events_init();

    // keyboard init
    lv_keyboard_set_textarea(ui_Keyboard, ui_MessageInputArea);
}

/**
 * @brief set active button, panel and top panel
 * 
 * @param b button to set active
 * @param p main panel to set active
 * @param tp top panel to set active
 */
void TFTView_320x240::ui_set_active(lv_obj_t* b, lv_obj_t* p, lv_obj_t* tp) {
    if (activeButton) {
        lv_obj_set_style_border_width(activeButton, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
        lv_obj_set_style_bg_img_recolor_opa(activeButton, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
    }
    lv_obj_set_style_border_width(b, 3, LV_PART_MAIN| LV_STATE_DEFAULT);
    //lv_obj_set_style_bg_img_recolor(b, lv_color_hex(0x67EA94), LV_PART_MAIN| LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor_opa(b, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

    if (activePanel)
      _ui_flag_modify(activePanel, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);

    _ui_flag_modify(p, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);

    if (tp) {
        if (activeTopPanel) {
            _ui_flag_modify(activeTopPanel, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        }
        _ui_flag_modify(tp, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
        activeTopPanel = tp;
    }

    activeButton = b;
    activePanel = p;

    _ui_flag_modify(ui_Keyboard, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
}


void TFTView_320x240::ui_events_init(void) {
    // just a test to implement callback via non-static lambda function
    auto ui_event_HomeButton = [](lv_event_t * e) {
        lv_event_code_t event_code = lv_event_get_code(e);
        if (event_code == LV_EVENT_CLICKED) {
            TFTView_320x240& view = *static_cast<TFTView_320x240*>(e->user_data);
            view.ui_set_active(ui_HomeButton, ui_HomePanel, ui_TopPanel);
        }
    };

    // main button events
    lv_obj_add_event_cb(ui_HomeButton, ui_event_HomeButton, LV_EVENT_ALL, this);  // uses lambda above
    lv_obj_add_event_cb(ui_NodesButton, this->ui_event_NodesButton, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_GroupsButton, this->ui_event_GroupsButton, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_MessagesButton, this->ui_event_MessagesButton, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_MapButton, this->ui_event_MapButton, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_SettingsButton, this->ui_event_SettingsButton, LV_EVENT_ALL, NULL);

    // node and channel buttons
    // TODO: node buttons are dynamic (implement array)
    lv_obj_add_event_cb(ui_NodeButton, ui_event_NodeButtonClicked, LV_EVENT_ALL, ui_UserNameLabel);

    lv_obj_add_event_cb(ui_ChannelButton0, ui_event_ChannelButtonClicked, LV_EVENT_ALL, ui_ChannelLabel0);
    lv_obj_add_event_cb(ui_ChannelButton1, ui_event_ChannelButtonClicked, LV_EVENT_ALL, ui_ChannelLabel1);
    lv_obj_add_event_cb(ui_ChannelButton2, ui_event_ChannelButtonClicked, LV_EVENT_ALL, ui_ChannelLabel2);
    lv_obj_add_event_cb(ui_ChannelButton3, ui_event_ChannelButtonClicked, LV_EVENT_ALL, ui_ChannelLabel3);
    lv_obj_add_event_cb(ui_ChannelButton4, ui_event_ChannelButtonClicked, LV_EVENT_ALL, ui_ChannelLabel4);
    lv_obj_add_event_cb(ui_ChannelButton5, ui_event_ChannelButtonClicked, LV_EVENT_ALL, ui_ChannelLabel5);
    lv_obj_add_event_cb(ui_ChannelButton6, ui_event_ChannelButtonClicked, LV_EVENT_ALL, ui_ChannelLabel6);
    lv_obj_add_event_cb(ui_ChannelButton7, ui_event_ChannelButtonClicked, LV_EVENT_ALL, ui_ChannelLabel7);

    // keyboard
    lv_obj_add_event_cb(ui_Keyboard, ui_event_Keyboard, LV_EVENT_ALL, this);

}

#if 0  // defined above as lambda function for tests
void TDeckGUI::ui_event_HomeButton(lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t* target = lv_event_get_target(e);
    if (event_code == LV_EVENT_CLICKED) {
        TDeckGUI::instance()->ui_set_active(ui_HomeButton, ui_HomePanel, ui_TopHomePanel);
    }
}
#endif

void TFTView_320x240::ui_event_NodesButton( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_CLICKED) {
        TFTView_320x240::instance()->ui_set_active(ui_NodesButton, ui_NodesPanel, ui_TopNodesPanel);
    }
}

void TFTView_320x240::ui_event_NodeButtonClicked(lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);
    if(event_code == LV_EVENT_CLICKED) {
        //  set color and text of clicked node 
        lv_label_t* userNameLabel = (lv_label_t*)e->user_data;
        lv_label_set_text(ui_TopNodeLabel, userNameLabel->text);
        TFTView_320x240::instance()->ui_set_active(ui_MessagesButton, ui_MessagesPanel, ui_TopMessagePanel);
    }
}

void TFTView_320x240::ui_event_GroupsButton( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_CLICKED) {
        TFTView_320x240::instance()->ui_set_active(ui_GroupsButton, ui_GroupsPanel, ui_TopGroupsPanel);
    }
}

void TFTView_320x240::ui_event_ChannelButtonClicked(lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);
    if(event_code == LV_EVENT_CLICKED) {
        // set color and text of clicked group channel 
        lv_label_t* userNameLabel = (lv_label_t*)e->user_data;
        lv_label_set_text(ui_TopGroupChatLabel, userNameLabel->text);
        TFTView_320x240::instance()->ui_set_active(ui_MessagesButton, ui_MessagesPanel, ui_TopGroupChatPanel);
    }
}

void TFTView_320x240::ui_event_MessagesButton( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_CLICKED) {
        TFTView_320x240::instance()->ui_set_active(ui_MessagesButton, ui_MessagesPanel, ui_TopMessagePanel);
    }
}

void TFTView_320x240::ui_event_MapButton( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_CLICKED) {
        TFTView_320x240::instance()->ui_set_active(ui_MapButton, ui_MapPanel, ui_TopMapPanel);
    }
}

void TFTView_320x240::ui_event_SettingsButton( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_CLICKED) {
        TFTView_320x240::instance()->ui_set_active(ui_SettingsButton, ui_SettingsPanel, ui_TopSettingsPanel);
    }
}

void TFTView_320x240::ui_event_Keyboard(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if(event_code == LV_EVENT_CLICKED) {
        lv_obj_t* kb = lv_event_get_target(e);
        uint32_t btn_id = lv_keyboard_get_selected_btn(kb);

        switch (btn_id) {
            case 22: {  // enter (filtered out by one-liner text input area, so we replace it)
                lv_obj_t* ta = lv_keyboard_get_textarea(kb);
                lv_textarea_add_char(ta, ' ');
                lv_textarea_add_char(ta, CR_REPLACEMENT);
                break;
            }
            case 35: {  // keyboard
                lv_keyboard_set_popovers(ui_Keyboard, !lv_btnmatrix_get_popovers(kb));
                break;
            }
            case 36: {  // left
                break;
            }
            case 38: {  // right
                break;
            }
            case 39: {  // checkmark
                lv_obj_t* ta = lv_keyboard_get_textarea(kb);
                char* txt = (char*)lv_textarea_get_text(ta);
                lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
                if (ta == ui_MessageInputArea) {
                    Serial.println(txt);
                    TFTView_320x240::instance()->addMessage(txt);
                }
                lv_textarea_set_text(ta, "");
                break;
            }
            default: {  
                const char* txt = lv_keyboard_get_btn_text(kb, btn_id);
                Serial.print("btn id: ");
                Serial.print(btn_id);
                Serial.print(", btn: ");
                Serial.println(txt);
            }
        }
    }
}

void TFTView_320x240::addMessage(char* msg) {
    lv_obj_t* hiddenPanel = lv_obj_create(ui_MessagesContainer);
    lv_obj_set_width(hiddenPanel, lv_pct(100));
    lv_obj_set_height(hiddenPanel, LV_SIZE_CONTENT);
    lv_obj_set_align(hiddenPanel, LV_ALIGN_CENTER);
    lv_obj_clear_flag(hiddenPanel, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_radius(hiddenPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(hiddenPanel, lv_color_hex(0x303030), LV_PART_MAIN | LV_STATE_DEFAULT);
    //lv_obj_set_style_bg_opa(hiddenPanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(hiddenPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(hiddenPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(hiddenPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(hiddenPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(hiddenPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t* textLabel = lv_label_create(hiddenPanel);
    lv_obj_set_width(textLabel, lv_pct(60));
    lv_obj_set_height(textLabel, LV_SIZE_CONTENT);
    lv_obj_set_y(textLabel, 0);
    lv_obj_set_x(textLabel, lv_pct(40));
    lv_obj_set_align(textLabel, LV_ALIGN_LEFT_MID);

    // tweak to allow multiple lines in single line text area
    for (int i=0; i < strlen(msg); i++) 
        if (msg[i] == CR_REPLACEMENT) msg[i] = '\n';
    lv_label_set_text(textLabel, msg);
    lv_obj_set_style_text_color(textLabel, lv_color_hex(0xF0F0F0), LV_PART_MAIN | LV_STATE_DEFAULT);
    //lv_obj_set_style_text_opa(textLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(textLabel, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(textLabel, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(textLabel, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(textLabel, lv_color_hex(0x404040), LV_PART_MAIN | LV_STATE_DEFAULT);
    //lv_obj_set_style_bg_opa(textLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(textLabel, lv_color_hex(0x67EA94), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(textLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(textLabel, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(textLabel, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(textLabel, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(textLabel, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(textLabel, 1, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_scroll_to_view(hiddenPanel, LV_ANIM_ON);
}

void TFTView_320x240::addNode(uint32_t nodeNum, uint8_t channel, const char *userShort, const char *userLong, eRole role)
{
    // lv_obj nodePanel children
    // [0]: img
    // [1]: btn
    // [2]: lbl user long
    // [3]: lbl user short
    // [4]: lbl battery
    // [5]: lbl lastHeard
    // [6]: lbl signal

    lv_obj_t *p = lv_obj_create(ui_NodesPanel);
    nodes[nodeNum] = p;
    nodeCount++;
    updateNodesOnline("%d of %d nodes online");

    lv_obj_set_height(p, 50);
    lv_obj_set_width(p, lv_pct(100));
    lv_obj_set_align(p, LV_ALIGN_CENTER);
    lv_obj_clear_flag(p, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM); /// Flags
    lv_obj_set_scrollbar_mode(p, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_bg_color(p, lv_color_hex(0x404040), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(p, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(p, lv_color_hex(0x808080), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(p, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(p, 1, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *img = lv_img_create(p);
    setNodeImage(nodeNum, role, img);

    lv_obj_set_width(img, LV_SIZE_CONTENT);
    lv_obj_set_height(img, LV_SIZE_CONTENT);
    lv_obj_set_x(img, -5);
    lv_obj_set_y(img, -10);
    // lv_obj_set_align( img, LV_ALIGN_LEFT_MID );
    lv_obj_add_flag(img, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(img, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_t *ui_NodeButton = lv_btn_create(p);
    lv_obj_set_height(ui_NodeButton, 50);
    lv_obj_set_width(ui_NodeButton, lv_pct(50));
    lv_obj_set_x(ui_NodeButton, -13);
    lv_obj_set_y(ui_NodeButton, 0);
    lv_obj_set_align(ui_NodeButton, LV_ALIGN_LEFT_MID);
    lv_obj_add_flag(ui_NodeButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_set_style_bg_color(ui_NodeButton, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_NodeButton, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_NodeButton, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_NodeButton, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_NodeButton, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui_NodeButton, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui_NodeButton, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ln_lbl = lv_label_create(p);
    lv_obj_set_width(ln_lbl, LV_SIZE_CONTENT);
    lv_obj_set_height(ln_lbl, LV_SIZE_CONTENT);
    lv_obj_set_x(ln_lbl, -6);
    lv_obj_set_y(ln_lbl, 12);
    lv_obj_set_align(ln_lbl, LV_ALIGN_BOTTOM_LEFT);
    lv_label_set_text(ln_lbl, userLong);
    lv_obj_set_style_text_color(ln_lbl, lv_color_hex(0xF0F0F0), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ln_lbl, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ln_lbl, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *sn_lbl = lv_label_create(p);
    lv_obj_set_width(sn_lbl, LV_SIZE_CONTENT);
    lv_obj_set_height(sn_lbl, LV_SIZE_CONTENT);
    lv_obj_set_x(sn_lbl, 25);
    lv_obj_set_y(sn_lbl, -3);
    lv_obj_set_align(sn_lbl, LV_ALIGN_LEFT_MID);
    lv_label_set_text(sn_lbl, userShort);
    lv_obj_set_style_text_color(sn_lbl, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(sn_lbl, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_BatteryLabel = lv_label_create(p);
    lv_obj_set_width(ui_BatteryLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_BatteryLabel, LV_SIZE_CONTENT);
    lv_obj_set_y(ui_BatteryLabel, -15);
    lv_obj_set_x(ui_BatteryLabel, 8);
    lv_obj_set_align(ui_BatteryLabel, LV_ALIGN_RIGHT_MID);
    lv_label_set_text(ui_BatteryLabel, "");
    lv_obj_set_style_text_color(ui_BatteryLabel, lv_color_hex(0xF0F0F0), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_BatteryLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_BatteryLabel, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_BatteryLabel, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_lastHeardLabel = lv_label_create(p);
    lv_obj_set_width(ui_lastHeardLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_lastHeardLabel, LV_SIZE_CONTENT);
    lv_obj_set_align(ui_lastHeardLabel, LV_ALIGN_RIGHT_MID);
    lv_obj_set_x(ui_lastHeardLabel, 8);
    lv_obj_set_y(ui_lastHeardLabel, 0);
    lv_label_set_text(ui_lastHeardLabel, "");
    lv_obj_set_style_text_color(ui_lastHeardLabel, lv_color_hex(0xF0F0F0), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_lastHeardLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_lastHeardLabel, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_lastHeardLabel, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
    ui_lastHeardLabel->user_data = 0;

    lv_obj_t *ui_SignalLabel = lv_label_create(p);
    lv_obj_set_width(ui_SignalLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_SignalLabel, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_SignalLabel, 8);
    lv_obj_set_y(ui_SignalLabel, 12);
    lv_obj_set_align(ui_SignalLabel, LV_ALIGN_BOTTOM_RIGHT);
    lv_label_set_text(ui_SignalLabel, "");
    lv_obj_set_style_text_color(ui_SignalLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_SignalLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_SignalLabel, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_NodeButton, ui_event_NodeButtonClicked, LV_EVENT_ALL, ln_lbl);
}

void TFTView_320x240::setMyInfo(uint32_t nodeNum) {
    ownNode = nodeNum;
    nodes[ownNode] = ui_NodePanel;
}

void TFTView_320x240::setDeviceMetaData(int hw_model, const char* version, bool has_bluetooth, bool has_wifi, bool has_eth, bool can_shutdown) {

}

void TFTView_320x240::addOrUpdateNode(uint32_t nodeNum, uint8_t channel, const char* userShort, const char* userLong, eRole role) {
    if (nodes.find(nodeNum) == nodes.end()) {
        addNode(nodeNum, 0, userShort, userLong, role);
    }
    else {
        updateNode(nodeNum, channel, userShort, userLong, role);
    }
}

void TFTView_320x240::updateNode(uint32_t nodeNum, uint8_t channel, const char* userShort, const char* userLong, eRole role) {
    auto it = nodes.find(nodeNum); 
    if (it != nodes.end()) {
        lv_label_set_text(it->second->LV_OBJ_IDX(node_lbl_idx), userLong);
        it->second->LV_OBJ_IDX(node_lbl_idx)->user_data = (void*)strlen(userLong);
        lv_label_set_text(it->second->LV_OBJ_IDX(node_lbs_idx), userShort);
        setNodeImage(nodeNum, role, it->second->LV_OBJ_IDX(node_img_idx));
    }
}

void TFTView_320x240::updatePosition(uint32_t nodeNum, int32_t lat, int32_t lon, int32_t alt, uint32_t precision) {
    auto it = nodes.find(nodeNum); 
    if (it != nodes.end()) {
        //TODO
    }
}

void TFTView_320x240::updateMetrics(uint32_t nodeNum, uint32_t bat_level, float voltage, float chUtil, float airUtil, uint32_t lastHeard) {
    auto it = nodes.find(nodeNum); 
    if (it != nodes.end()) {
        char buf[32];
        if (it->first == ownNode) {
           sprintf(buf, "Util %0.1f%% %0.1f%%", chUtil, airUtil);
           lv_label_set_text(it->second->LV_OBJ_IDX(node_sig_idx), buf);
        }

        if (bat_level != 0 || voltage != 0) {
            bat_level = min(bat_level, (uint32_t)100);
            sprintf(buf, "%d%% %0.2fV", bat_level, voltage);
            lv_label_set_text(it->second->LV_OBJ_IDX(node_bat_idx), buf);
        }
        time_t curtime;
        time(&curtime);
        lastHeard = min(curtime, (time_t)lastHeard); // correct future values
        bool isOnline = lastHeartToString(lastHeard, buf);
        lv_label_set_text(it->second->LV_OBJ_IDX(node_lh_idx), buf);
        it->second->LV_OBJ_IDX(node_lh_idx)->user_data = (void*)lastHeard;
        if (isOnline) {
            nodesOnline++;
            updateNodesOnline("%d of %d nodes online");
        }
    }
}

void TFTView_320x240::updateSignalStrength(uint32_t nodeNum, int32_t rssi, float snr) {
    if (rssi == 0 && snr == 0) return;
    auto it = nodes.find(nodeNum); 
    if (it != nodes.end()) {
        // if userNameLong is too long, skip printing rssi/snr
        char buf[30];
        if ((size_t)it->second->LV_OBJ_IDX(node_lbl_idx)->user_data <= 20) {
            sprintf(buf, "rssi: %d snr: %.1f", rssi, snr);
        }
        else {
            sprintf(buf, "snr: %.1f", snr);
        }
        lv_label_set_text(it->second->LV_OBJ_IDX(node_sig_idx), buf);
    }
}

void TFTView_320x240::packetReceived(uint32_t from, uint32_t to, uint32_t portnum, const uint8_t* bytes, uint32_t size) {
    MeshtasticView::packetReceived(from, to, portnum, bytes, size);
}

void TFTView_320x240::updateChannelConfig(uint32_t index, const char* name, const uint8_t* psk, uint32_t psk_size, uint8_t role) {

}


// -------- helpers --------

void TFTView_320x240::removeNode(uint32_t nodeNum) {
    auto it = nodes.find(nodeNum); 
    if (it != nodes.end()) {

    }
}

void TFTView_320x240::setNodeImage(uint32_t nodeNum, eRole role, lv_obj_t* img) {
    uint32_t color = nodeColor(nodeNum);
    switch (role) {
    case client:
    case client_mute:
    case client_hidden: 
    case tak: {
        lv_img_set_src(img, &ui_img_2104440450);
        break;
    }
    case router_client: {
        lv_img_set_src(img, &ui_img_2095618903);
        break;
    }
    case repeater:
    case router: {
        lv_img_set_src(img, &ui_img_1003866492);
        break;
    }
    case tracker:
    case sensor:
    case lost_and_found:
    case tak_tracker: {
        lv_img_set_src(img, &ui_img_519712240);
        break;
    }
    default:
        lv_img_set_src(img, &ui_img_2104440450);
        break;
    }

    lv_obj_set_style_img_recolor(img, lv_color_hex(color), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(img, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
}

/**
 * @brief Update last heard display/user_data/counter to current time
 * 
 * @param nodeNum 
 */
void TFTView_320x240::updateLastHeard(uint32_t nodeNum) {
    auto it = nodes.find(nodeNum); 
    if (it != nodes.end()) {
        time_t curtime;
        time(&curtime);
        time_t lastHeard = (time_t)it->second->LV_OBJ_IDX(node_lh_idx)->user_data;
        it->second->LV_OBJ_IDX(node_lh_idx)->user_data = (void*)curtime;
        lv_label_set_text(it->second->LV_OBJ_IDX(node_lh_idx), "now");
        if (curtime - lastHeard >= 900) {
            nodesOnline++;    
            updateNodesOnline("%d of %d nodes online");
        }
    }
}


/**
 * @brief update last heard display for all nodes; also update nodes online
 * 
 */
void TFTView_320x240::updateAllLastHeard(void) {
    uint16_t online = 0;
    time_t lastHeard;
    for (auto& it: nodes) {
        char buf[20];
        if (it.first == ownNode) { // own node is always now, so do update 
            time_t curtime;
            time(&curtime);
            lastHeard = curtime;
            it.second->LV_OBJ_IDX(node_lh_idx)->user_data = (void*)lastHeard;
        }
        else {
            lastHeard = (time_t)it.second->LV_OBJ_IDX(node_lh_idx)->user_data;
        }
        bool isOnline = lastHeartToString(lastHeard, buf);
        lv_label_set_text(it.second->LV_OBJ_IDX(node_lh_idx), buf);
        if (isOnline) online++;
    }
    nodesOnline = online;
    updateNodesOnline("%d of %d nodes online");
}

void TFTView_320x240::task_handler(void) {
    MeshtasticView::task_handler();

    // call every 60s
    time_t curtime;
    time(&curtime);
    if (curtime - lastrun >= 60) {
        lastrun = curtime;
        updateAllLastHeard();
    }
}

#endif