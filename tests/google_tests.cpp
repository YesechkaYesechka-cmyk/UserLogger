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
        Date date("         Thu Jun 27 09:46 - 22:54 (10+13:08)");
        EXPECT_TRUE(date.m_month == "Jun");
        EXPECT_TRUE(date.m_day == 27);
        EXPECT_TRUE(date.m_hour == 9);
        EXPECT_TRUE(date.m_minutes == 46);
    }
    {
        Date date("     Sat Jul 13 18:08   still logged in");
        EXPECT_TRUE(date.m_month == "Jul");
        EXPECT_TRUE(date.m_day == 13);
        EXPECT_TRUE(date.m_hour == 18);
        EXPECT_TRUE(date.m_minutes == 8);
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
        EXPECT_TRUE(session.m_username == "user");
        EXPECT_TRUE(session.m_tty_name == "pts/2");
        EXPECT_TRUE(session.m_hostname == "192.168.0.8");
        EXPECT_TRUE(session.m_date.m_month == "Jul");
        EXPECT_TRUE(session.m_date.m_day == 13);
        EXPECT_TRUE(session.m_date.m_hour == 19);
        EXPECT_TRUE(session.m_date.m_minutes == 19);
        EXPECT_TRUE(session.m_date.m_duration.m_hour == 0);
        EXPECT_TRUE(session.m_date.m_duration.m_minutes == 0);
    }
    {
        LogSession session("confident tty2         tty2             Wed Jun 26 23:15 - 22:53 (10+23:38)");
        EXPECT_TRUE(session.m_username == "confident");
        EXPECT_TRUE(session.m_tty_name == "tty2");
        EXPECT_TRUE(session.m_hostname == "tty2");
        EXPECT_TRUE(session.m_date.m_month == "Jun");
        EXPECT_TRUE(session.m_date.m_day == 26);
        EXPECT_TRUE(session.m_date.m_hour == 23);
        EXPECT_TRUE(session.m_date.m_minutes == 15);
        EXPECT_TRUE(session.m_date.m_duration.m_day == 10);
        EXPECT_TRUE(session.m_date.m_duration.m_hour == 23);
        EXPECT_TRUE(session.m_date.m_duration.m_minutes == 38);
    }
    {
        LogSession session("clinic_88 seat0        login screen     Thu Jun 27 09:46 - 22:54 (10+13:08)");
        EXPECT_TRUE(session.m_username == "clinic_88");
        EXPECT_TRUE(session.m_tty_name == "seat0");
        EXPECT_TRUE(session.m_hostname == "login screen");
        EXPECT_TRUE(session.m_date.m_month == "Jun");
        EXPECT_TRUE(session.m_date.m_day == 27);
        EXPECT_TRUE(session.m_date.m_hour == 9);
        EXPECT_TRUE(session.m_date.m_minutes == 46);
        EXPECT_TRUE(session.m_date.m_duration.m_day == 10);
        EXPECT_TRUE(session.m_date.m_duration.m_hour == 13);
        EXPECT_TRUE(session.m_date.m_duration.m_minutes == 8);
    }
    {
        LogSession session("clinic_88 tty4         tty4             Thu Jun 27 09:46 - down  (16+09:11)");
        EXPECT_TRUE(session.m_username == "clinic_88");
        EXPECT_TRUE(session.m_tty_name == "tty4");
        EXPECT_TRUE(session.m_hostname == "tty4");
        EXPECT_TRUE(session.m_date.m_month == "Jun");
        EXPECT_TRUE(session.m_date.m_day == 27);
        EXPECT_TRUE(session.m_date.m_hour == 9);
        EXPECT_TRUE(session.m_date.m_minutes == 46);
        EXPECT_TRUE(session.m_date.m_duration.m_day == 16);
        EXPECT_TRUE(session.m_date.m_duration.m_hour == 9);
        EXPECT_TRUE(session.m_date.m_duration.m_minutes == 11);
    }
    {
        LogSession session("reboot   system boot  6.8.0-35-generic Wed Jun 19 18:05 - 22:48 (7+04:42)");
        EXPECT_TRUE(session.m_username == "reboot");
        EXPECT_TRUE(session.m_tty_name == "system boot");
        EXPECT_TRUE(session.m_hostname == "6.8.0-35-generic");
        EXPECT_TRUE(session.m_date.m_month == "Jun");
        EXPECT_TRUE(session.m_date.m_day == 19);
        EXPECT_TRUE(session.m_date.m_hour == 18);
        EXPECT_TRUE(session.m_date.m_minutes == 5);
        EXPECT_TRUE(session.m_date.m_duration.m_day == 7);
        EXPECT_TRUE(session.m_date.m_duration.m_hour == 4);
        EXPECT_TRUE(session.m_date.m_duration.m_minutes == 42);
    }
}

TEST(LogSessionTests, WithoutDuration) {

    {
          LogSession session("reboot   system boot  6.8.0-38-generic Sat Jul 13 18:58   still running");
          EXPECT_TRUE(session.m_username == "reboot");
          EXPECT_TRUE(session.m_tty_name == "system boot");
          EXPECT_TRUE(session.m_hostname == "6.8.0-38-generic");
          EXPECT_TRUE(session.m_date.m_month == "Jul");
          EXPECT_TRUE(session.m_date.m_day == 13);
          EXPECT_TRUE(session.m_date.m_hour == 18);
          EXPECT_TRUE(session.m_date.m_minutes == 58);
          EXPECT_TRUE(session.m_date.m_duration.m_day == 0);
          EXPECT_TRUE(session.m_date.m_duration.m_hour == 0);
          EXPECT_TRUE(session.m_date.m_duration.m_minutes == 0);
    }
       {
            LogSession session("user     :0           :0               Sat Jul 13 18:58   still logged in");
            EXPECT_TRUE(session.m_username == "user");
            EXPECT_TRUE(session.m_tty_name == ":0");
            EXPECT_TRUE(session.m_hostname == ":0");
            EXPECT_TRUE(session.m_date.m_month == "Jul");
            EXPECT_TRUE(session.m_date.m_day == 13);
            EXPECT_TRUE(session.m_date.m_hour == 18);
            EXPECT_TRUE(session.m_date.m_minutes == 58);
            EXPECT_TRUE(session.m_date.m_duration.m_day == 0);
            EXPECT_TRUE(session.m_date.m_duration.m_hour == 0);
            EXPECT_TRUE(session.m_date.m_duration.m_minutes == 0);
        }
        {
           LogSession session("user     seat0        login screen     Sat Jul 13 18:58   still logged in");
           EXPECT_TRUE(session.m_username == "user");
           EXPECT_TRUE(session.m_tty_name == "seat0");
           EXPECT_TRUE(session.m_hostname == "login screen");
           EXPECT_TRUE(session.m_date.m_month == "Jul");
           EXPECT_TRUE(session.m_date.m_day == 13);
           EXPECT_TRUE(session.m_date.m_hour == 18);
           EXPECT_TRUE(session.m_date.m_minutes == 58);
           EXPECT_TRUE(session.m_date.m_duration.m_day == 0);
           EXPECT_TRUE(session.m_date.m_duration.m_hour == 0);
           EXPECT_TRUE(session.m_date.m_duration.m_minutes == 0);
       }
}