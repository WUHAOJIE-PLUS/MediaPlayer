#ifndef QSS_H
#define QSS_H

#include <string>
using std::string;

string buttonQss = R"(
   QPushButton {
       font: 14pt "Helvetica Neue", sans-serif;
       color: rgb(255, 255, 255);
       border: none;
       padding: 6px 12px;  /* macOS 标准按钮内边距 */
   }
   QPushButton::menu-indicator:open {
       image: url(qrc:/down_arrow.svg);
       subcontrol-position: right center;
       subcontrol-origin: padding;
   }
   QPushButton::menu-indicator:closed {
       image: url(qrc:/up_arrow.svg);
       subcontrol-position: right center;
       subcontrol-origin: padding;
   }
)";

string menuQss = R"(
   QMenu {
       background-color: rgb(53, 63, 73);
       color: white;
       border-radius: 6px; /* macOS 圆角 */
       padding: 4px;      /* 紧凑内边距 */
   }
   QMenu::item {
       font: 13pt "Helvetica Neue";
       padding: 8px 24px; /* 调整间距 */
       margin: 2px 4px;   /* 减少外边距 */
       background-color: transparent;
   }
   QMenu::item:selected {
       background-color: #3A3A3A;
       border-radius: 4px;
   }
)";


string menuItemQss = R"(
   QMenu {
       background-color: rgb(73, 73, 73);
       color: white;
       border-radius: 6px;        /* macOS 圆角风格 */
       padding: 4px;              /* 紧凑内边距 */
       margin: 0px;               /* 消除默认外边距 */
   }
   QMenu::item {
       font: 12pt "Helvetica Neue", sans-serif; /* macOS 系统字体 + pt 单位 */
       color: white;
       background-color: transparent;          /* 透明背景避免重叠 */
       padding: 8px 24px;         /* 调整左右内边距 */
       margin: 2px 4px;           /* 减少项间距 */
   }
   QMenu::item:selected {
       background-color: #3A3A3A; /* 更深的悬停色 */
       border-radius: 4px;        /* 圆角匹配菜单 */
   }
)";


#endif // QSS_H
