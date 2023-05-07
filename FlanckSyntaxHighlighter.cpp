#include "FlanckSyntaxHighlighter.h"

//! [0]
FlanckSyntaxHighlighter::FlanckSyntaxHighlighter(QTextDocument *parent)
        : QSyntaxHighlighter(parent)
{
    HighlightingRule rule;

    auto normalFormat = QTextCharFormat();
    normalFormat.setForeground(QBrush("#4C566A"));
    rule.format = normalFormat;
    rule.pattern = QRegularExpression(".+");
    highlightingRules.append(rule);

    auto klammerAufFormat = QTextCharFormat();
    klammerAufFormat.setForeground(QBrush("#88C0D0"));
    rule.format = klammerAufFormat;
    rule.pattern = QRegularExpression("\\[");
    highlightingRules.append(rule);

    auto klammerZuFormat = QTextCharFormat();
    klammerZuFormat.setForeground(QBrush("#88C0D0"));
    rule.format = klammerZuFormat;
    rule.pattern = QRegularExpression("\\]");
    highlightingRules.append(rule);

    auto colonFormat = QTextCharFormat();
    colonFormat.setForeground(QBrush("#B48EAD"));
    colonFormat.setFontWeight(QFont::ExtraBold);
    rule.format = colonFormat;
    rule.pattern = QRegularExpression(":");
    highlightingRules.append(rule);

    auto nullFormat = QTextCharFormat();
    nullFormat.setForeground(QBrush("#EBCB8B"));
    rule.format = nullFormat;
    rule.pattern = QRegularExpression("0");
    highlightingRules.append(rule);

    auto einsFormat = QTextCharFormat();
    einsFormat.setForeground(QBrush("#BF616A"));
    rule.format = einsFormat;
    rule.pattern = QRegularExpression("1");
    highlightingRules.append(rule);

}

void FlanckSyntaxHighlighter::highlightBlock(const QString &text) {
    for (const HighlightingRule &rule: std::as_const(highlightingRules)) {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }
}