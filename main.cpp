#include "src/FixEngine.h"

#include <iostream>

int main()
{
    const char* msg = "8=FIX.4.2|9=144|35=D|34=1|49=Trader123|56=BrokerXYZ|52=20241210-16:30:00.123|11=Order12345|55=EUR/USD|54=1|38=100000|40=2|44=1.1050|59=0|60=20241210-16:29:59.456|10=211|";
    
    const std::vector<fix::Tags> required_fields = {
        fix::Tags::Symbol_55,
        fix::Tags::Side_54,
        fix::Tags::Quantity_38
    };

    fix::interface::FixEngine fix_engine(msg, required_fields);

    auto [valid, res] = fix_engine.get_fields(required_fields);
    if (valid) {
        for (const auto itr : res) {
            std::cout << std::to_underlying(itr.first) << '=' << itr.second << '\n';
        }
    }

    return 0;
}
