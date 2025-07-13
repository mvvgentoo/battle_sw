#ifndef UNITPARAMS_HPP
#define UNITPARAMS_HPP

#include <string>
#include <unordered_map>

class UnitParams
{
public:
    void set(const std::string& key, int value)
    {
        _kvps[key] = value;
    }

    int get(const std::string& key, int defaultValue = 0) const
    {
        auto it = _kvps.find(key);
        return (it != _kvps.end()) ? it->second : defaultValue;
    }

private:
    std::unordered_map<std::string, int> _kvps;
};

#endif // UNITPARAMS_HPP
