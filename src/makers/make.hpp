#pragma once

#include "bunsan/utility/maker.hpp"

#include <string>
#include <vector>
#include <unordered_map>

#include <boost/optional.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/nvp.hpp>

namespace bunsan{namespace utility{namespace makers
{
    class make: public maker
    {
    public:
        struct config
        {
            template <typename Archive>
            void serialize(Archive &ar, const unsigned int)
            {
                ar & BOOST_SERIALIZATION_NVP(defines);
                ar & BOOST_SERIALIZATION_NVP(targets);
                ar & BOOST_SERIALIZATION_NVP(jobs);
            }

            std::unordered_map<std::string, std::string> defines; ///< for example {"DESTDIR": "/some/path"}
            std::vector<std::string> targets; ///< for example ["install"]
            boost::optional<std::size_t> jobs;
        };

    public:
        explicit make(const boost::filesystem::path &exe);

        void exec(
            const boost::filesystem::path &cwd,
            const std::vector<std::string> &targets) override;

        void setup(const boost::property_tree::ptree &ptree) override;

    private:
        std::vector<std::string> argv_(
            const std::vector<std::string> &targets) const;

    private:
        const boost::filesystem::path m_exe;
        config m_config;

    private:
        static const bool factory_reg_hook;
    };
}}}
