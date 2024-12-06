#include <gtest/gtest.h>
#include "user.h"
#include "log_session.h"

TEST(GECOS, GECOS_ctor_arg) {
    {
        GECOS gecos{"root"};
        EXPECT_TRUE(gecos.m_fullname == "root");
        //    EXPECT_STREQ(gecos.m_fullname.data(), "root");
        EXPECT_TRUE(gecos.m_address == "");
        EXPECT_TRUE(gecos.m_workmobile == "");
        EXPECT_TRUE(gecos.m_homemobile == "");
    }
    {
        GECOS gecos{"www-data"};
        EXPECT_TRUE(gecos.m_fullname == "www-data");
        EXPECT_TRUE(gecos.m_address == "");
        EXPECT_TRUE(gecos.m_workmobile == "");
        EXPECT_TRUE(gecos.m_homemobile == "");
    }
    {
        GECOS gecos{"Mailing List Manager"};
        EXPECT_TRUE(gecos.m_fullname == "Mailing List Manager");
        EXPECT_TRUE(gecos.m_address == "");
        EXPECT_TRUE(gecos.m_workmobile == "");
        EXPECT_TRUE(gecos.m_homemobile == "");
    }
    {
        GECOS gecos{"Gnats Bug-Reporting System (admin)"};
        EXPECT_TRUE(gecos.m_fullname == "Gnats Bug-Reporting System (admin)");
        EXPECT_TRUE(gecos.m_address == "");
        EXPECT_TRUE(gecos.m_workmobile == "");
        EXPECT_TRUE(gecos.m_homemobile == "");
    }
    {
        GECOS gecos{"systemd Resolver,,,"};
        EXPECT_TRUE(gecos.m_fullname == "systemd Resolver");
        EXPECT_TRUE(gecos.m_address == "");
        EXPECT_TRUE(gecos.m_workmobile == "");
        EXPECT_TRUE(gecos.m_homemobile == "");
    }
    {
        GECOS gecos{""};
        EXPECT_TRUE(gecos.m_fullname == "");
        EXPECT_TRUE(gecos.m_address == "");
        EXPECT_TRUE(gecos.m_workmobile == "");
        EXPECT_TRUE(gecos.m_homemobile == "");
    }
    {
        GECOS gecos{",,,"};
        EXPECT_TRUE(gecos.m_fullname == "");
        EXPECT_TRUE(gecos.m_address == "");
        EXPECT_TRUE(gecos.m_workmobile == "");
        EXPECT_TRUE(gecos.m_homemobile == "");
    }
    {
        GECOS gecos{"Jill Hill,828,212-555-0000,212-555-3456"};
        EXPECT_TRUE(gecos.m_fullname == "Jill Hill");
        EXPECT_TRUE(gecos.m_address == "828");
        EXPECT_TRUE(gecos.m_workmobile == "212-555-0000");
        EXPECT_TRUE(gecos.m_homemobile == "212-555-3456");
    }
   {
        GECOS gecos{"Jill Hill,828,212-555-0000,212-555-3456,jhill@example.com"};
        EXPECT_TRUE(gecos.m_fullname == "Jill Hill");
        EXPECT_TRUE(gecos.m_address == "828");
        EXPECT_TRUE(gecos.m_workmobile == "212-555-0000");
        EXPECT_TRUE(gecos.m_homemobile == "212-555-3456");
    }
    {
        GECOS gecos{"Jill Hill,828,,212-555-3456,jhill@example.com"};
        EXPECT_TRUE(gecos.m_fullname == "Jill Hill");
        EXPECT_TRUE(gecos.m_address == "828");
        EXPECT_TRUE(gecos.m_workmobile == "");
        EXPECT_TRUE(gecos.m_homemobile == "212-555-3456");
    }
}

TEST(User, User_ctor_arg) {
    {
        User user{"root:x:0:0:root:/root:zsh"};
        EXPECT_TRUE(user.m_username == "root");
        EXPECT_TRUE(user.m_uid == 0);
        EXPECT_TRUE(user.m_gid == 0);
        EXPECT_TRUE(user.m_gecos.m_fullname == "root");
        // EXPECT_TRUE(user.m_gecos.m_homemobile == "");
        EXPECT_TRUE(user.m_homedir_path == "/root");
        EXPECT_TRUE(user.m_interpretator == "zsh");
    }

    {
        User user{"www-data:x:33:33:www-data:/var/www:/usr/sbin/nologin"};
        EXPECT_TRUE(user.m_username == "www-data");
        EXPECT_TRUE(user.m_uid == 33);
        EXPECT_TRUE(user.m_gid == 33);
        EXPECT_TRUE(user.m_gecos.m_fullname == "www-data");
         EXPECT_TRUE(user.m_gecos.m_homemobile == "");
        EXPECT_TRUE(user.m_homedir_path == "/var/www");
        EXPECT_TRUE(user.m_interpretator == "/usr/sbin/nologin");
    }

    {
        User user{"list:x:38:38:Mailing List Manager:/var/list:/usr/sbin/nologin"};
        EXPECT_TRUE(user.m_username == "list");
        EXPECT_TRUE(user.m_uid == 38);
        EXPECT_TRUE(user.m_gid == 38);
        EXPECT_TRUE(user.m_gecos.m_fullname == "Mailing List Manager");
         EXPECT_TRUE(user.m_gecos.m_homemobile == "");
        EXPECT_TRUE(user.m_homedir_path == "/var/list");
        EXPECT_TRUE(user.m_interpretator == "/usr/sbin/nologin");
    }

    {
        User user{"gnats:x:41:41:Gnats Bug-Reporting System (admin):/var/lib/gnats:/usr/sbin/nologin"};
        EXPECT_TRUE(user.m_username == "gnats");
        EXPECT_TRUE(user.m_uid == 41);
        EXPECT_TRUE(user.m_gid == 41);
        EXPECT_TRUE(user.m_gecos.m_fullname == "Gnats Bug-Reporting System (admin)");
         EXPECT_TRUE(user.m_gecos.m_homemobile == "");
        EXPECT_TRUE(user.m_homedir_path == "/var/lib/gnats");
        EXPECT_TRUE(user.m_interpretator == "/usr/sbin/nologin");
    }

    {
        User user{"systemd-network:x:100:102:systemd Network Management,,,:/run/systemd:/usr/sbin/nologin"};
        EXPECT_TRUE(user.m_username == "systemd-network");
        EXPECT_TRUE(user.m_uid == 100);
        EXPECT_TRUE(user.m_gid == 102);
        EXPECT_TRUE(user.m_gecos.m_fullname == "systemd Network Management");
        EXPECT_TRUE(user.m_gecos.m_homemobile == "");
        EXPECT_TRUE(user.m_gecos.m_workmobile == "");
        EXPECT_TRUE(user.m_gecos.m_address == "");
        EXPECT_TRUE(user.m_homedir_path == "/run/systemd");
        EXPECT_TRUE(user.m_interpretator == "/usr/sbin/nologin");
    }

    {
        User user{"_apt:x:105:65534::/nonexistent:/usr/sbin/nologin"};
        EXPECT_TRUE(user.m_username == "_apt");
        EXPECT_TRUE(user.m_uid == 105);
        EXPECT_TRUE(user.m_gid == 65534);
        EXPECT_TRUE(user.m_gecos.m_fullname == "");
        EXPECT_TRUE(user.m_homedir_path == "/nonexistent");
        EXPECT_TRUE(user.m_interpretator == "/usr/sbin/nologin");
    }

    {
        User user{"_flatpak:x:136:146:Flatpak system-wide installation helper,,,:/nonexistent:/usr/sbin/nologin"};
        EXPECT_TRUE(user.m_username == "_flatpak");
        EXPECT_TRUE(user.m_uid == 136);
        EXPECT_TRUE(user.m_gid == 146);
        EXPECT_TRUE(user.m_gecos.m_fullname == "Flatpak system-wide installation helper");
        EXPECT_TRUE(user.m_gecos.m_homemobile == "");
        EXPECT_TRUE(user.m_gecos.m_workmobile == "");
        EXPECT_TRUE(user.m_gecos.m_address == "");
        EXPECT_TRUE(user.m_homedir_path == "/nonexistent");
        EXPECT_TRUE(user.m_interpretator == "/usr/sbin/nologin");
    }
}

TEST(Duration, IsCorrectMinutes) {
    {
        EXPECT_TRUE(IsCorrectMinutes("1") == -1);
        EXPECT_TRUE(IsCorrectMinutes("60") == -1);

        EXPECT_TRUE(IsCorrectMinutes("01") == 1);
        EXPECT_TRUE(IsCorrectMinutes("10") == 10);
        EXPECT_TRUE(IsCorrectMinutes("32") == 32);
    }
}

TEST(Duration, Duration_ctor_str) {
    {
        EXPECT_NO_THROW(Date::Duration dur("00:07"));
        Date::Duration dur("00:07");
        EXPECT_TRUE(dur.m_day==0);
        EXPECT_TRUE(dur.m_hour==0);
        EXPECT_TRUE(dur.m_minutes==7);
    }
    {
        EXPECT_THROW(Date::Duration dur("(10+23:38)"), std::exception);
    }
    {
        EXPECT_THROW(Date::Duration dur("(10+23:38"), std::exception);
    }
    {
        EXPECT_THROW(Date::Duration dur("(10+23:3"), std::exception);
    }
    {
        EXPECT_THROW(Date::Duration dur("(10+23:"), std::exception);
    }
    {
        EXPECT_THROW(Date::Duration dur("(10+23"), std::exception);
    }
    {
        EXPECT_THROW(Date::Duration dur("(10+2"), std::exception);
    }
    {
        EXPECT_THROW(Date::Duration dur("(10+"), std::exception);
    }
    {
        EXPECT_THROW(Date::Duration dur("(10"), std::exception);
    }
    {
        EXPECT_THROW(Date::Duration dur("("), std::exception);
    }
    {
        EXPECT_THROW(Date::Duration dur("10+23:3"), std::exception);
    }
    {
        EXPECT_THROW(Date::Duration dur("10+23:"), std::exception);
    }
    {
        EXPECT_THROW(Date::Duration dur("10+23"), std::exception);
    }
    {
        EXPECT_THROW(Date::Duration dur("10+"), std::exception);
    }
    {
        Date::Duration dur("10+23:38");
        EXPECT_TRUE(dur.m_day==10);
        EXPECT_TRUE(dur.m_hour==23);
        EXPECT_TRUE(dur.m_minutes==38);
    }
    {
        Date::Duration dur("2+04:25");
        EXPECT_TRUE(dur.m_day==2);
        EXPECT_TRUE(dur.m_hour==4);
        EXPECT_TRUE(dur.m_minutes==25);
    }

}

TEST(DATE, date_str) {
    {
        Date date("Mon Jul  8 21:31");
        EXPECT_TRUE(date.m_month == "Jul");
        EXPECT_TRUE(date.m_day == 8);
        EXPECT_TRUE(date.m_hour == 21);
        EXPECT_TRUE(date.m_minutes == 31);
    }
    {
        Date date("       Mon Jul  8 21:31");
        EXPECT_TRUE(date.m_month == "Jul");
        EXPECT_TRUE(date.m_day == 8);
        EXPECT_TRUE(date.m_hour == 21);
        EXPECT_TRUE(date.m_minutes == 31);
    }
    {
        Date date("   Mon       Jul  8 21:31");
        EXPECT_TRUE(date.m_month == "Jul");
        EXPECT_TRUE(date.m_day == 8);
        EXPECT_TRUE(date.m_hour == 21);
        EXPECT_TRUE(date.m_minutes == 31);
    }
    {
        Date date("Sat Jul 13 18:58");
        EXPECT_TRUE(date.m_month == "Jul");
        EXPECT_TRUE(date.m_day == 13);
        EXPECT_TRUE(date.m_hour == 18);
        EXPECT_TRUE(date.m_minutes == 58);
    }
    {
        Date date("Sun Jun  2 00:40");
        EXPECT_TRUE(date.m_month == "Jun");
        EXPECT_TRUE(date.m_day == 2);
        EXPECT_TRUE(date.m_hour == 0);
        EXPECT_TRUE(date.m_minutes == 40);
    }
    {
        Date date("Sun May 19 23:03");
        EXPECT_TRUE(date.m_month == "May");
        EXPECT_TRUE(date.m_day == 19);
        EXPECT_TRUE(date.m_hour == 23);
        EXPECT_TRUE(date.m_minutes == 3);
    }
    {
        Date date("Sun May 19 00:03");
        EXPECT_TRUE(date.m_month == "May");
        EXPECT_TRUE(date.m_day == 19);
        EXPECT_TRUE(date.m_hour == 0);
        EXPECT_TRUE(date.m_minutes == 3);
    }
    {
        Date date("Sun May 19 03:00");
        EXPECT_TRUE(date.m_month == "May");
        EXPECT_TRUE(date.m_day == 19);
        EXPECT_TRUE(date.m_hour == 3);
        EXPECT_TRUE(date.m_minutes == 0);
    }

    {
        Date date("Sun May 19 00:00");
        EXPECT_TRUE(date.m_month == "May");
        EXPECT_TRUE(date.m_day == 19);
        EXPECT_TRUE(date.m_hour == 0);
        EXPECT_TRUE(date.m_minutes == 0);
    }

    {
        EXPECT_THROW(Date date("May 19 23:03"), std::exception);
    }
    {
        EXPECT_THROW(Date date("May 19 23:    03"), std::exception);
    }
    {
        EXPECT_THROW(Date date("Sun May 19 2 23:03"), std::exception);
    }
    {
        EXPECT_THROW(Date date("Sun May 19    23 03"), std::exception);
    }
    {
        EXPECT_THROW(Date date("Sun May 19    23:3"), std::exception);
    }
    {
        EXPECT_THROW(Date date("Sun May 19    3:30"), std::exception);
    }
    {
        EXPECT_THROW(Date date("Sun May 19    2:3"), std::exception);
    }
    {
        EXPECT_THROW(Date date("Sun May 19    :3"), std::exception);
    }
    {
        EXPECT_THROW(Date date("Sun May 19    12:"), std::exception);
    }
    {
        EXPECT_THROW(Date date("Sun May 19    1233"), std::exception);
    }
    {
        EXPECT_THROW(Date date("Sun May 19    00:0"), std::exception);
    }
}


TEST(LogSessionTests, ValidLogSessionStrings) {
    // Тест с корректной строкой
    {
        LogSession session("user     pts/2        192.168.0.8      Sat Jul 13 19:19 - 19:19  (00:00)");
        EXPECT_TRUE(session.getUsername() == "user");
        EXPECT_TRUE(session.getTtyName() == "pts/2");
        EXPECT_TRUE(session.getHostname() == "192.168.0.8");
        EXPECT_TRUE(session.getDateParams().m_month == "Jul");
        EXPECT_TRUE(session.getDateParams().m_day == 13);
        EXPECT_TRUE(session.getDateParams().m_hour == 19);
        EXPECT_TRUE(session.getDateParams().m_minutes == 19);
        EXPECT_TRUE(session.getDateParams().duration.m_hour == 0);
        EXPECT_TRUE(session.getDateParams().duration.m_minutes == 0);
    }
}