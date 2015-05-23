#define BOOST_TEST_MODULE archiver
#include <boost/test/unit_test.hpp>

#include <bunsan/testing/test_tools.hpp>

#include "utility_fixture.hpp"

#include <bunsan/utility/archiver.hpp>

#include <boost/filesystem/operations.hpp>

BOOST_FIXTURE_TEST_SUITE(archiver, utility_fixture)

BOOST_AUTO_TEST_SUITE(_7z)

BOOST_AUTO_TEST_CASE(pack)
{
    const auto ar = bu::archiver::instance("7z", resolver);
    MOCK_EXPECT(executor->sync_execute).calls(
        [](const bunsan::process::context &ctx) {
            BUNSAN_IF_CHECK_EQUAL(ctx.arguments().size(), 5)
            {
                BOOST_CHECK_EQUAL(ctx.arguments()[0], "7z");
                BOOST_CHECK_EQUAL(ctx.arguments()[1], "a");
                BOOST_CHECK_EQUAL(ctx.arguments()[2], "--");
                BOOST_CHECK_EQUAL(ctx.arguments()[3],
                                  boost::filesystem::current_path() / "archive.");
                BOOST_CHECK_EQUAL(ctx.arguments()[4], "file");
            }
            return 0;
        });
    ar->pack("archive", "file");
}

BOOST_AUTO_TEST_CASE(pack_contents)
{
    const auto ar = bu::archiver::instance("7z", resolver);
    MOCK_EXPECT(executor->sync_execute).calls(
        [](const bunsan::process::context &ctx) {
            BUNSAN_IF_CHECK_EQUAL(ctx.arguments().size(), 5)
            {
                BOOST_CHECK_EQUAL(ctx.current_path(), boost::filesystem::current_path() / "dir");
                BOOST_CHECK_EQUAL(ctx.arguments()[0], "7z");
                BOOST_CHECK_EQUAL(ctx.arguments()[1], "a");
                BOOST_CHECK_EQUAL(ctx.arguments()[2], "--");
                BOOST_CHECK_EQUAL(ctx.arguments()[3],
                                  boost::filesystem::current_path() / "archive.");
                BOOST_CHECK_EQUAL(ctx.arguments()[4], ".");
            }
            return 0;
        });
    ar->pack_contents("archive", "dir");
}

BOOST_AUTO_TEST_CASE(unpack)
{
    const auto ar = bu::archiver::instance("7z", resolver);
    MOCK_EXPECT(executor->sync_execute).calls(
        [](const bunsan::process::context &ctx) {
            BUNSAN_IF_CHECK_EQUAL(ctx.arguments().size(), 5)
            {
                BOOST_CHECK_EQUAL(ctx.arguments()[0], "7z");
                BOOST_CHECK_EQUAL(ctx.arguments()[1], "x");
                BOOST_CHECK_EQUAL(ctx.arguments()[2], "-odir");
                BOOST_CHECK_EQUAL(ctx.arguments()[3], "--");
                BOOST_CHECK_EQUAL(ctx.arguments()[4], "archive");
            }
            return 0;
        });
    ar->unpack("archive", "dir");
}

BOOST_AUTO_TEST_SUITE_END() // _7z

BOOST_AUTO_TEST_SUITE(tar)

BOOST_AUTO_TEST_CASE(pack)
{
    const auto ar = bu::archiver::instance("tar", resolver);
    MOCK_EXPECT(executor->sync_execute).calls(
        [](const bunsan::process::context &ctx) {
            BUNSAN_IF_CHECK_EQUAL(ctx.arguments().size(), 8)
            {
                BOOST_CHECK_EQUAL(ctx.arguments()[0], "tar");
                BOOST_CHECK_EQUAL(ctx.arguments()[1], "--create");
                BOOST_CHECK_EQUAL(ctx.arguments()[2], "--file");
                BOOST_CHECK_EQUAL(ctx.arguments()[3],
                                  boost::filesystem::current_path() / "archive");
                BOOST_CHECK_EQUAL(ctx.arguments()[4], "--directory");
                BOOST_CHECK_EQUAL(ctx.arguments()[5], boost::filesystem::current_path());
                BOOST_CHECK_EQUAL(ctx.arguments()[6], "--");
                BOOST_CHECK_EQUAL(ctx.arguments()[7], "file");
            }
            return 0;
        });
    ar->pack("archive", "file");
}

BOOST_AUTO_TEST_CASE(pack_contents)
{
    const auto ar = bu::archiver::instance("tar", resolver);
    MOCK_EXPECT(executor->sync_execute).calls(
        [](const bunsan::process::context &ctx) {
            BUNSAN_IF_CHECK_EQUAL(ctx.arguments().size(), 8)
            {
                BOOST_CHECK_EQUAL(ctx.arguments()[0], "tar");
                BOOST_CHECK_EQUAL(ctx.arguments()[1], "--create");
                BOOST_CHECK_EQUAL(ctx.arguments()[2], "--file");
                BOOST_CHECK_EQUAL(ctx.arguments()[3],
                                  boost::filesystem::current_path() / "archive");
                BOOST_CHECK_EQUAL(ctx.arguments()[4], "--directory");
                BOOST_CHECK_EQUAL(ctx.arguments()[5],
                                  boost::filesystem::current_path() / "dir");
                BOOST_CHECK_EQUAL(ctx.arguments()[6], "--");
                BOOST_CHECK_EQUAL(ctx.arguments()[7], ".");
            }
            return 0;
        });
    ar->pack_contents("archive", "dir");
}

BOOST_AUTO_TEST_CASE(unpack)
{
    const auto ar = bu::archiver::instance("tar", resolver);
    MOCK_EXPECT(executor->sync_execute).calls(
        [](const bunsan::process::context &ctx) {
            BUNSAN_IF_CHECK_EQUAL(ctx.arguments().size(), 6)
            {
                BOOST_CHECK_EQUAL(ctx.arguments()[0], "tar");
                BOOST_CHECK_EQUAL(ctx.arguments()[1], "--extract");
                BOOST_CHECK_EQUAL(ctx.arguments()[2], "--file");
                BOOST_CHECK_EQUAL(ctx.arguments()[3],
                                  boost::filesystem::current_path() / "archive");
                BOOST_CHECK_EQUAL(ctx.arguments()[4], "--directory");
                BOOST_CHECK_EQUAL(ctx.arguments()[5],
                                  boost::filesystem::current_path() / "dir");
            }
            return 0;
        });
    ar->unpack("archive", "dir");
}

BOOST_AUTO_TEST_SUITE_END() // tar

BOOST_AUTO_TEST_SUITE_END() // archiver
