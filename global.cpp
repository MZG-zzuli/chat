#include "global.h"

std::function<void(QWidget* widget)> repolish=[](QWidget* widget)
{
    widget->style()->unpolish(widget);
    widget->style()->polish(widget);
};
QString gate_url_prefix="http://127.0.0.1";
