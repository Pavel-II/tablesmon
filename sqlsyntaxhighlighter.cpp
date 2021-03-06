#include "sqlsyntaxhighlighter.h"

//! [0]
SQLSyntaxHighlighter::SQLSyntaxHighlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    HighlightingRule rule;

    keywordFormat.setForeground(Qt::darkBlue);
    keywordFormat.setFontWeight(QFont::Bold);
    QStringList keywordPatterns;

    keywordPatterns << "select\\b" << "\\from\\b" << "\\where\\b" << "\\and\\b" << "\\case\\b" << "\\when\\b"
                    << "\\then\\b" << "\\else\\b" << "\\distinct\\b" << "\\all\\b" << "\\null\\b"
                    << "\\is\\b" << "\\like\\b" << "\\between\\b" << "\\not\\b" << "\\count\\b"
                    << "\\group\\b" << "\\by\\b" << "\\having\\b" << "\\order\\b" << "\\inner\\b"
                    << "\\outer\\b" << "\\right\\b" << "\\left\\b" << "\"join\\b" << "\\on\\b"
                    << "\\using\\b" << "\\union\\b" << "\\exists\\b" << "\\in\\b" << "\\as\\b"
                    << "\\intersect\\b" << "\\except\\b" << "\\coalesce\\b" << "\\insert\\b" << "\\delete\\b" << "\\into\\b" << "\\update";

    foreach (const QString &pattern, keywordPatterns) {
        rule.pattern = QRegularExpression(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
//! [0] //! [1]
    }
//! [1]

//! [2]
    classFormat.setFontWeight(QFont::Bold);
    classFormat.setForeground(Qt::darkMagenta);
    rule.pattern = QRegularExpression("\\bQ[A-Za-z]+\\b");
    rule.format = classFormat;
    highlightingRules.append(rule);
//! [2]

//! [3]
    singleLineCommentFormat.setForeground(Qt::red);
    rule.pattern = QRegularExpression("//[^\n]*");
    rule.format = singleLineCommentFormat;
    highlightingRules.append(rule);

    multiLineCommentFormat.setForeground(Qt::green);
//! [3]
///////////////////////////
//    quotationFormat.setForeground(Qt::green);
//    rule.pattern = QRegularExpression("-- ");
//    rule.format = multiLineCommentFormat;
//    highlightingRules.append(rule);
///////////////////////////
//! [4]
    quotationFormat.setForeground(Qt::darkGreen);
    rule.pattern = QRegularExpression("\".*\"");
    rule.format = quotationFormat;
    highlightingRules.append(rule);
//! [4]

//! [5]
    functionFormat.setFontItalic(true);
    functionFormat.setForeground(Qt::blue);
    rule.pattern = QRegularExpression("\\b[A-Za-z0-9_]+(?=\\()");
    rule.format = functionFormat;
    highlightingRules.append(rule);
//! [5]

//! [6]
    commentStartExpression = QRegularExpression("/\\*");
    commentEndExpression = QRegularExpression("\\*/");
}
//! [6]

//! [7]
void SQLSyntaxHighlighter::highlightBlock(const QString &text)
{
    foreach (const HighlightingRule &rule, highlightingRules) {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }
//! [7] //! [8]
    setCurrentBlockState(0);
//! [8]

//! [9]
    int startIndex = 0;
    if (previousBlockState() != 1)
        startIndex = text.indexOf(commentStartExpression);

//! [9] //! [10]
    while (startIndex >= 0) {
//! [10] //! [11]
        QRegularExpressionMatch match = commentEndExpression.match(text, startIndex);
        int endIndex = match.capturedStart();
        int commentLength = 0;
        if (endIndex == -1) {
            setCurrentBlockState(1);
            commentLength = text.length() - startIndex;
        } else {
            commentLength = endIndex - startIndex
                            + match.capturedLength();
        }
        setFormat(startIndex, commentLength, multiLineCommentFormat);
        startIndex = text.indexOf(commentStartExpression, startIndex + commentLength);
    }
}
//! [11]
