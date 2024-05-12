#pragma once

#include <gmock/gmock.h>
#include "x01_mainwindow_if.h"
#include "mainwindow_if.h"

class CX01MainWindowMock : public IX01MainWindow
{
public:

  CX01MainWindowMock(QWidget * iParent = nullptr)
  {}

  MOCK_METHOD(void, display_dart1, (uint32_t), (override));
  MOCK_METHOD(void, display_dart2, (uint32_t), (override));
  MOCK_METHOD(void, display_dart3, (uint32_t), (override));
  MOCK_METHOD(void, erase_dart1, (), (override));
  MOCK_METHOD(void, erase_dart2, (), (override));
  MOCK_METHOD(void, erase_dart3, (), (override));
  MOCK_METHOD(void, submit_score_to_player, (uint32_t, uint32_t, uint32_t, const QVector<QString>&), (override));
  MOCK_METHOD(void, update_finishes, (uint32_t, uint32_t), (override));
  MOCK_METHOD(void, set_focus_to_submit_button, (), (override));
  MOCK_METHOD(void, display_score, (uint32_t), (override));
  MOCK_METHOD(void, connect_main_window_slots, (), (override));
  MOCK_METHOD(void, submit_button_clicked_slot, (), (override));
  MOCK_METHOD(void, undo_button_clicked_slot, (), (override));

//  MOCK_METHOD(void, update_players, (const EUpdateType), (override));
//  MOCK_METHOD(void, reset_scores_of_all_players, (), (override));
//  MOCK_METHOD(void, inactivate_players, (uint32_t, bool, bool), (override));
//  MOCK_METHOD(void, create_snapshots_of_all_players, (), (override));
//  MOCK_METHOD(void, handle_game_won, (uint32_t), (override));
//  MOCK_METHOD(void, setAttribute, (Qt::WidgetAttribute, bool), (override));
//  MOCK_METHOD(void, show, (), (override));
//  MOCK_METHOD(void, set_active_player, (uint32_t), (override));
//  MOCK_METHOD(void, add_players, (), (override));
//  MOCK_METHOD(void, save_current_game, (), (override));
//  MOCK_METHOD(bool, game_finished, (), (const, override));
//  MOCK_METHOD(void, start_new_game_with_same_settings, (), (override));
//  MOCK_METHOD(void, clear_group_box_widgets, (), (override));
//  MOCK_METHOD(void, set_global_finished, (), (override));
//  MOCK_METHOD(void, handle_update_default, (), (override));
//  MOCK_METHOD(void, handle_update_leg, (), (override));
//  MOCK_METHOD(void, handle_update_set, (), (override));
//  MOCK_METHOD(void, inactivate_all_players, (), (override));
//  MOCK_METHOD(void, unset_leg_begin_for_all_players, (), (override));
//  MOCK_METHOD(void, unset_set_begin_for_all_players, (), (override));
};
