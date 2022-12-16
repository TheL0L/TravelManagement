#pragma once

/* Structure for holding prices, all values stored in USD. */
struct PriceSheet
{
    /* prices are based on destination, each dest. has unique id. */
    int destination_id;
    int destination_ticket = 0, flight_class = 0, per_reserved_day = 0;
    int swimming_pool = 0, gym = 0, other_sports = 0;
    int spa = 0, beauty_salon = 0;
};
