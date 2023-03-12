enum custom_keycodes
{
  KC_MY_BTN1 = KEYBALL_SAFE_RANGE, // Remap上では 0x5DAF
  KC_MY_BTN2,                      // Remap上では 0x5DB0
  KC_MY_BTN3,                      // Remap上では 0x5DB1
};

// マクロキーを設定
bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
  current_keycode = keycode;

  switch (keycode)
  {
  case KC_MY_BTN1:
  case KC_MY_BTN2:
  case KC_MY_BTN3:
  {
    report_mouse_t currentReport = pointing_device_get_report();

    // どこのビットを対象にするか。 Which bits are to be targeted?
    uint8_t btn = 1 << (keycode - KC_MY_BTN1);

    if (record->event.pressed)
    {
      // キーダウン時
      // ビットORは演算子の左辺と右辺の同じ位置にあるビットを比較して、両方のビットのどちらかが「1」の場合に「1」にします。
      // Bit OR compares bits in the same position on the left and right sides of the operator and sets them to "1" if either of both bits is "1".
      currentReport.buttons |= btn;
      state = CLICKING;
    }
    else
    {
      // キーアップ時
      // ビットANDは演算子の左辺と右辺の同じ位置にあるビットを比較して、両方のビットが共に「1」の場合だけ「1」にします。
      // Bit AND compares the bits in the same position on the left and right sides of the operator and sets them to "1" only if both bits are "1" together.
      currentReport.buttons &= ~btn;
      enable_click_layer();
    }

    pointing_device_set_report(currentReport);
    pointing_device_send();
    return false;
  }

  // 自動クリックレイヤーでLang1とLang2を押せるようにする
  case KC_LANG1:
  case KC_LANG2:
  {
    if (state == CLICKABLE)
    {
      if (record->event.pressed)
      {
        // キーダウン時
        enable_click_layer();
        return true;
      }
      else
      {
        // キーアップ時
        disable_click_layer();
      }
    }
  }

  // クリックすると state が SWIPE になり、離したら NONE になる
  // MOD系
  case KC_LCMD:
    if (record->event.pressed)
    {
      // キーダウン時
      state = SWIPE;
      register_code(keycode);
    }
    else
    {
      // キーアップ時
      clear_mods();
      disable_click_layer();
    }
    return false;

  // TAP系（フリック風）
  case KC_T:
    if (record->event.pressed)
    {
      // キーダウン時
      state = SWIPE;
      tap_code(keycode);
    }
    else
    {
      // キーアップ時
      disable_click_layer();
    }
    return false;

  // TAP系（キーリピートあり）
  case KC_D:
    if (record->event.pressed)
    {
      // キーダウン時
      state = SWIPE;
      is_repeat = true;
    }
    else
    {
      // キーアップ時
      if (is_swiped == false)
      {
        tap_code(keycode);
      }

      disable_click_layer();
      is_swiped = false;
      is_repeat = false;
    }
    return false;

  default:
    if (record->event.pressed)
    {
      // キーダウン時
      disable_click_layer();
    }
  }

  return true;
}