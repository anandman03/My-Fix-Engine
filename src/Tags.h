#pragma once

#include <cstdint>

namespace fix
{
    enum class Tags
    {
        FixVersion_8 = 8,
        BodyLength_9 = 9,
        CheckSum_10 = 10,
        MsgSeqNum_34 = 34,
        MsgType_35 = 35,
        Quantity_38 = 38,
        SenderCompId_49 = 49,
        SendingTime_52 = 52,
        Side_54 = 54,
        Symbol_55 = 55,
        SenderCompId_56 = 56
    };
} // namespace fix
