#pragma once

#include "transaction.h"

namespace html
{
    class node;
}

class TransactionReader
{
public:
    void ParseHtmlFile(std::string path);

    std::vector<Transaction>& GetTransactions();

private:
    void ParseHtmlText(std::string htmlText);
    void ParseWellList(html::node* wellList);
    void ParseDateHeader(html::node* dateHeader);
    void ParseWell(html::node* well);

private:
    std::vector<Transaction> transactions;
};