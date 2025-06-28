#ifndef INIPARSER_H
#define INIPARSER_H

#include "lib/SimpleIni.h"
#include <string>
#include <iostream>

class IniParser
{
public:
    IniParser(const std::string& filename) :
        m_filename(filename)
    {
        m_ini.SetUnicode();
    }

    bool Load()
    {
        SI_Error rc = m_ini.LoadFile(m_filename.c_str());
        if (rc < 0) {
            std::cerr << "IniParser::load() Failed to load file: " << m_filename << std::endl;
            return false;
        }
        return true;
    }

    bool Save()
    {
        SI_Error rc = m_ini.SaveFile(m_filename.c_str());
        if (rc < 0) {
            std::cerr << "IniParser::save() Failed to save file: " << m_filename << std::endl;
            return false;
        }
        return true;
    }

    std::string Read(const std::string& section, const std::string& key, const std::string& defaultValue = "")
    {
        const char* val = m_ini.GetValue(section.c_str(), key.c_str(), defaultValue.c_str());
        return val ? std::string(val) : defaultValue;
    }

    void Write(const std::string& section, const std::string& key, const std::string& value)
    {
        m_ini.SetValue(section.c_str(), key.c_str(), value.c_str());
    }

private:
    std::string m_filename;
    CSimpleIniA m_ini;
};

#endif // INIPARSER_H
