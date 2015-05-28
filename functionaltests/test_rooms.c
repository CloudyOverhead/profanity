#include <glib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdlib.h>
#include <string.h>

#include <stabber.h>
#include <expect.h>

#include "proftest.h"

void
rooms_query(void **state)
{
    stbbr_for("confreq",
        "<iq id=\"confreq\" type=\"result\" to=\"stabber@localhost/profanity\" from=\"conference.localhost\">"
            "<query xmlns=\"http://jabber.org/protocol/disco#items\">"
                "<item jid=\"chatroom@conference.localhost\" name=\"A chat room\"/>"
                "<item jid=\"hangout@conference.localhost\" name=\"Another chat room\"/>"
            "</query>"
        "</iq>"
    );

    prof_connect("stabber@localhost", "password");

    prof_input("/rooms");

    assert_true(stbbr_last_received(
        "<iq id=\"confreq\" to=\"conference.localhost\" type=\"get\">"
            "<query xmlns=\"http://jabber.org/protocol/disco#items\"/>"
        "</iq>"
    ));

    assert_true(prof_output("chatroom@conference.localhost, (A chat room)"));
    assert_true(prof_output("hangout@conference.localhost, (Another chat room)"));
}
