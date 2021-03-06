#pragma once

#include "widgets/BaseWindow.hpp"

#include <QPushButton>
#include <QStackedLayout>
#include <QVBoxLayout>
#include <QWidget>
#include <pajlada/settings/setting.hpp>

namespace chatterino {

class SettingsPage;
class SettingsDialogTab;
class ModerationPage;

enum class SettingsDialogPreference {
    NoPreference,
    Accounts,
    ModerationActions,
};

class SettingsDialog : public BaseWindow
{
public:
    SettingsDialog();

    static SettingsDialog *getHandle();  // may be NULL
    static void showDialog(SettingsDialogPreference preferredTab =
                               SettingsDialogPreference::NoPreference);

protected:
    virtual void scaleChangedEvent(float newDpi) override;
    virtual void themeChangedEvent() override;

private:
    static SettingsDialog *handle;

    void refresh();

    void initUi();
    void addTabs();
    void addTab(SettingsPage *page, Qt::Alignment alignment = Qt::AlignTop);
    void selectTab(SettingsDialogTab *tab);
    void selectPage(SettingsPage *page);

    void onOkClicked();
    void onCancelClicked();

    struct {
        QWidget *tabContainerContainer{};
        QVBoxLayout *tabContainer{};
        QStackedLayout *pageStack{};
        QPushButton *okButton{};
        QPushButton *cancelButton{};
        ModerationPage *moderationPage{};
    } ui_;
    std::vector<SettingsDialogTab *> tabs_;
    SettingsDialogTab *selectedTab_{};

    friend class SettingsDialogTab;
};

}  // namespace chatterino
