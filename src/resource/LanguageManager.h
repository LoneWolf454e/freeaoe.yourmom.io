#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace genie {
class LangFile;
}

class LanguageManager
{
public:
    static LanguageManager *Inst();
    bool initialize();

    static const std::string &getString(unsigned int id);

private:
    LanguageManager() = default;
    void loadLangFile(const std::string &filename);
    bool loadTxtFile(const std::string &filename);

    std::vector<std::shared_ptr<genie::LangFile>> m_langFiles;
    std::unordered_map<unsigned int, std::string> m_cache;
    bool m_isHd = false;
};

