#include <iostream>
#include <boost/log/trivial.hpp>

int main(int, char*[])
{
    BOOST_LOG_TRIVIAL(trace) << "This is a trace severity message";
    BOOST_LOG_TRIVIAL(debug) << "This is a debug severity message";
    BOOST_LOG_TRIVIAL(info) << "This is an informational severity message"; 
    BOOST_LOG_TRIVIAL(warning) << "This is a warning severity message";
    BOOST_LOG_TRIVIAL(error) << "This is an error severity message";
    BOOST_LOG_TRIVIAL(fatal) << "and this is a fatal severity message";
    std::cin.get();
    return 0;
}