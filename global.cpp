#include "global.h"

std::function<void(QWidget* widget)> repolish=[](QWidget* widget)
{
    widget->style()->unpolish(widget);
    widget->style()->polish(widget);
};
