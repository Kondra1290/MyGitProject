#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <libintl.h>

#define _(String) gettext(String)

void guess_number() {
    int low = 1, high = 100;
    int mid;
    char response[10];

    printf(_("Загадайте число от 1 до 100.\n"));
    printf(_("Я буду задавать вопросы. Отвечайте 'да', 'нет' или 'больше'.\n"));

    while (low <= high) {
        mid = (low + high) / 2;
        printf(_("Число больше %d? (да/нет)\n"), mid);

        if (scanf("%s", response) != 1) {
            printf(_("Ошибка ввода. Попробуйте снова.\n"));
            continue;
        }

        if (strcmp(response, _("да")) == 0) {
            low = mid + 1;
        } else if (strcmp(response, _("нет")) == 0) {
            high = mid - 1;
        } else {
            printf(_("Неправильный ответ. Пожалуйста, ответьте 'да' или 'нет'.\n"));
        }
    }

    printf(_("Ваше число: %d\n"), low);
}

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    setlocale(LC_ALL, "en_US.UTF-8");
    bindtextdomain("guess", "./locale");
    textdomain("guess");

    guess_number();
    return 0;
}
