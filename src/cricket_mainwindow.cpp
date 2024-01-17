#include "cricket_mainwindow.h"
#include "ui_cricket_mainwindow.h"
#include "groupbox_cricket.h"
#include "cricket_class.h"
#include <QString>
#include <QMessageBox>
#include <QCloseEvent>


CCricketMainWindow::CCricketMainWindow(QWidget * iParent, const CSettings & ipSettings)
  : QMainWindow(iParent)
  , mUi(new Ui::CCricketMainWindow)
  , mpSettings(ipSettings)
  , mNumberOfPlayers(mpSettings.mPlayersList.size())
{
  mUi->setupUi(this);
  QWidget::setWindowTitle("Cricket");

  for (uint32_t i = 0; i < mNumberOfPlayers; i++)
  {
    mCricketPlayer.push_back(new CCricketClass(this, i+1, mpSettings));
    mCricketBox.push_back(new CCricketGroupBox(this, mpSettings, i+1, mCricketPlayer[i]));
    mCricketBox[i]->setAttribute(Qt::WA_DeleteOnClose);
    mCricketBox[i]->set_inactive();
    mUi->gridLayoutCricket->addWidget(mCricketBox[i], i<4 ? 0 : 1, i%4);
  }

  mCricketBox[mActivePlayer]->set_set_begin();
  mCricketBox[mActivePlayer]->set_leg_begin();
  mCricketBox[mActivePlayer]->set_active();
}

CCricketMainWindow::~CCricketMainWindow()
{
  delete mUi;
  for (auto player : mCricketPlayer)
  {
    delete player;
  }
  for (auto box : mCricketBox)
  {
    delete box;
  }
}

void CCricketMainWindow::closeEvent(QCloseEvent * iEvent)
{
  QMessageBox::StandardButton resBtn = QMessageBox::question(this, "Quit game",
                                                             tr("Are you sure you want to quit the game?\n"),
                                                             QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
                                                             QMessageBox::No);
  if (resBtn != QMessageBox::Yes) iEvent->ignore();
  else iEvent->accept();
}

void CCricketMainWindow::set_active_player(uint32_t iPlayer)
{
  mActivePlayer = iPlayer;
}

void CCricketMainWindow::update_active_player()
{
  mActivePlayer = (mActivePlayer + 1) % mNumberOfPlayers;
}

void CCricketMainWindow::inactivate_all_players()
{
  for (uint32_t i = 0; i < mNumberOfPlayers; i++)
  {
    mCricketBox[i]->set_inactive();
  }
}

void CCricketMainWindow::handle_update_default()
{
  update_active_player();
  inactivate_all_players();
  mCricketBox[mActivePlayer]->set_active();
}

void CCricketMainWindow::handle_update_leg()
{
  inactivate_all_players();
  for (uint32_t i = 0; i < mNumberOfPlayers; i++)
  {
    if (mCricketBox[i]->has_begun_leg())
    {
      mCricketBox[i]->unset_leg_begin();
      mActivePlayer = i;
      update_active_player();
      mCricketBox[mActivePlayer]->set_active();
      mCricketBox[mActivePlayer]->set_leg_begin();
      break;
    }
  }
}

void CCricketMainWindow::unset_leg_begin_for_all_players()
{
  for (uint32_t i = 0; i < mNumberOfPlayers; i++)
  {
    mCricketBox[i]->unset_leg_begin();
  }
}

void CCricketMainWindow::handle_update_set()
{
  inactivate_all_players();
  unset_leg_begin_for_all_players();
  for (uint32_t i = 0; i < mNumberOfPlayers; i++)
  {
    if (mCricketBox[i]->has_begun_set())
    {
      mCricketBox[i]->unset_set_begin();
      mActivePlayer = i;
      update_active_player();
      mCricketBox[mActivePlayer]->set_active();
      mCricketBox[mActivePlayer]->set_leg_begin();
      mCricketBox[mActivePlayer]->set_set_begin();
      break;
    }
  }
  for (auto box: mCricketBox)
  {
    box->reset_legs();
    box->set_lcd_legs();
  }
}

void CCricketMainWindow::update_players(const EUpdateType iType)
{
  if (iType == EUpdateType::DEFAULT)
  {
    handle_update_default();
  }
  else if (iType == EUpdateType::LEG)
  {
    handle_update_leg();
  }
  else if (iType == EUpdateType::SET)
  {
    handle_update_set();
  }
}

void CCricketMainWindow::reset_scores_of_all_players()
{
  for (uint32_t i = 0; i < mNumberOfPlayers; i++)
  {
    mCricketBox[i]->reset();
  }
}

void CCricketMainWindow::handle_game_won(uint32_t iPlayerNumber)
{
  for (uint32_t i = 0; i < mNumberOfPlayers; i++)
  {
    mCricketBox[i]->set_finished();
  }

  mCricketBox[iPlayerNumber]->close_cricket_input();
  QString name = mCricketBox[iPlayerNumber]->get_player_number();
  QString text = name + " has won the game. Congratulations!. ";
  QMessageBox::about(this,"Game finished", text);
}

void CCricketMainWindow::unset_set_begin_for_all_players()
{
  for (uint32_t i = 0; i < mNumberOfPlayers; i++)
  {
    mCricketBox[i]->unset_set_begin();
  }
}

void CCricketMainWindow::inactivate_players(uint32_t iPlayerNumber, bool iLegStarted, bool iSetStarted)
{
  inactivate_all_players();
  set_active_player(iPlayerNumber);

  if (!iLegStarted)
  {
    unset_leg_begin_for_all_players();
    mCricketBox[iPlayerNumber]->set_leg_begin();
  }

  if (!iSetStarted)
  {
    unset_leg_begin_for_all_players();
    unset_set_begin_for_all_players();
    mCricketBox[iPlayerNumber]->set_leg_begin();
    mCricketBox[iPlayerNumber]->set_set_begin();
  }
}

void CCricketMainWindow::update_history_of_all_players()
{
  for (uint32_t i = 0; i < mNumberOfPlayers; i++)
  {
    mCricketBox[i]->update_history();
  }
}

bool CCricketMainWindow::is_slot_free(const ECricketSlots iSlot, uint32_t iPlayer) const
{
  bool free = false;
  for (uint32_t i = 0; i < mNumberOfPlayers; i++)
  {
    if (i != iPlayer)
    {
      free |= mCricketBox[i]->get_slot(iSlot) < 3;
    }
  }
  return free;
}

bool CCricketMainWindow::is_score_bigger(uint32_t iScore) const
{
  bool result = true;
  for (uint32_t i = 0; i < mNumberOfPlayers; i++)
  {
    result = result && mCricketBox[i]->get_score() <= iScore;
  }
  return result;
}

bool CCricketMainWindow::is_score_smaller(uint32_t iScore) const
{
  bool result = true;
  for (uint32_t i = 0; i < mNumberOfPlayers; i++)
  {
    result = result && mCricketBox[i]->get_score() >= iScore;
  }
  return result;
}

void CCricketMainWindow::increase_slot_score(const ECricketSlots iSlot, uint32_t iPoints)
{
  for (uint32_t i = 0; i < mNumberOfPlayers; i++)
  {
    if (mCricketBox[i]->get_slot(iSlot) != 3)
    {
      mCricketBox[i]->increase_extra_points(iSlot, iPoints);
    }
    else
    {
      mCricketBox[i]->increase_extra_points(iSlot, 0);
    }
  }
}

QVector<uint32_t> CCricketMainWindow::compute_extra_points(const ECricketSlots iSlot, uint32_t iPoints, uint32_t iPlayer)
{
  QVector<uint32_t> extraPoints = {};

  for (uint32_t i = 0; i < mNumberOfPlayers; i++)
  {
    if (i != iPlayer)
    {
      uint32_t extra = 0;
      if (mCricketBox[i]->get_slot(iSlot) != 3)
      {
        extra = mCricketBox[i]->get_extra_points(iSlot) + iPoints;
      }
      else
      {
        extra = mCricketBox[i]->get_extra_points(iSlot);
      }
      extraPoints.push_back(extra);
    }
  }
  return extraPoints;
}

void CCricketMainWindow::set_scores()
{
  for (uint32_t i = 0; i < mNumberOfPlayers; i++)
  {
    mCricketBox[i]->set_score();
  }
}

void CCricketMainWindow::update_extra_points_labels()
{
  for (uint32_t i = 0; i < mNumberOfPlayers; i++)
  {
    mCricketBox[i]->update_extra_points_labels();
  }
}

void CCricketMainWindow::update_darts(uint32_t iPlayer)
{
  for (uint32_t i = 0; i < mNumberOfPlayers; i++)
  {
    if (i != iPlayer)
    {
      mCricketBox[i]->update_darts({""});
    }
  }
}
