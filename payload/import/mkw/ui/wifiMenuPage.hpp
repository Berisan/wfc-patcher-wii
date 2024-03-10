#pragma once

#include "messagePopupPage.hpp"
#include "sectionManager.hpp"
#include <cstddef>

namespace mkw::UI
{

#if RMC

class WifiMenuPage : public Page
{
public:
    void showMessageOfTheDay()
    {
        if (s_hasSeenMessageOfTheDay) {
            return;
        }

        pushMessageOfTheDayMessagePopup();
        s_hasSeenMessageOfTheDay = true;
    }

    static void SetMessageOfTheDay(wchar_t* messageOfTheDay)
    {
        s_messageOfTheDay = messageOfTheDay;
    }

    static wchar_t* MessageOfTheDayBuffer()
    {
        return s_messageOfTheDayBuffer;
    }

    static size_t MessageOfTheDayBufferSize()
    {
        return sizeof(s_messageOfTheDayBuffer);
    }

private:
    void pushMessageOfTheDayMessagePopup()
    {
        Section* section = SectionManager::Instance()->currentSection();
        MessagePopupPage* messagePopupPage =
            section->page<MessagePopupPage>(PageId::MessagePopup);

        FormatParam formatParam{};
        formatParam.strings[0] = s_messageOfTheDay;

        messagePopupPage->reset();
        messagePopupPage->setWindowMessage(0x19CA, &formatParam);

        push(PageId::MessagePopup, Animation::Next);
    }

    /* 0x044 */ u8 _044[0xF34 - 0x044];

    static const wchar_t* s_messageOfTheDay;
    static wchar_t s_messageOfTheDayBuffer[256];
    static bool s_hasSeenMessageOfTheDay;
};

static_assert(sizeof(WifiMenuPage) == 0xF34);

#endif

} // namespace mkw::UI

#if RMC

extern "C" {
__attribute__((__used__)) static void
WifiMenuPage_showMessageOfTheDay(mkw::UI::WifiMenuPage* wifiMenuPage)
{
    wifiMenuPage->showMessageOfTheDay();
}
}

#endif
