#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define CANDY_KINDS   6U
#define BASKET_MAX    8U
#define NAME_LEN     16U

typedef struct {
    char     name[NAME_LEN];
    uint16_t price;
    uint16_t stock;
    uint16_t sold;
} Candy_t;

typedef struct {
    uint8_t  candyId;
    uint8_t  qty;
} Line_t;

static Candy_t shelf[CANDY_KINDS];
static Line_t  basket[BASKET_MAX];
static uint8_t basketLines;
static uint32_t cashDrawer;


static void     openShop(void);
static void     showShelf(void);
static void     addToBasket(void);
static void     removeFromBasket(void);
static uint32_t basketTotal(void);
static void     showBasket(void);
static void     checkout(void);
static void     giveChange(uint32_t change);
static uint8_t  bestSeller(void);
static void     dayReport(void);

int main(void) {
    openShop();
    int choice;
    do {
        printf("\nMenu:\n");
        printf("1. Show shelf\n");
        printf("2. Add to basket\n");
        printf("3. Remove from basket\n");
        printf("4. Show basket\n");
        printf("5. Checkout\n");
        printf("6. Day report\n");
        printf("0. Exit\n");
        printf("Choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            return 0;
        }
        switch (choice) {
            case 1: showShelf(); break;
            case 2: addToBasket(); break;
            case 3: removeFromBasket(); break;
            case 4: showBasket(); break;
            case 5: checkout(); break;
            case 6: dayReport(); break;
            case 0: break;
            default: printf("Unknown option!\n"); break;
        }
    } while (choice != 0);
    return 0;
}


static void openShop(void) {
    const char *names[CANDY_KINDS] = {"Lollipop","Chocolate","Gum","Caramel","Marshmallow","Cookie"};
    const uint16_t prices[CANDY_KINDS] = {50, 200, 25, 100, 150, 75};
    const uint16_t stocks[CANDY_KINDS] = {20, 10, 30, 15, 25, 12};
    for (uint8_t i = 0; i < CANDY_KINDS; i++) {
        strncpy(shelf[i].name, names[i], NAME_LEN);
        shelf[i].price = prices[i];
        shelf[i].stock = stocks[i];
        shelf[i].sold = 0;
    }
    basketLines = 0;
    cashDrawer = 0;
}

static void showShelf(void) {
    printf("\nShelf:\n");
    for (uint8_t i = 0; i < CANDY_KINDS; i++) {
        printf("%u: %-12s %3u piastres | %s\n",
               i, shelf[i].name, shelf[i].price,
               (shelf[i].stock == 0) ? "SOLD OUT" : "");
        if (shelf[i].stock > 0) {
            printf("   Stock: %u\n", shelf[i].stock);
        }
    }
}

static void     addToBasket(void){


}

static void     removeFromBasket(void){


}

static uint32_t basketTotal(void){


}

static void     showBasket(void){


}

static void     checkout(void){


}

static void     giveChange(uint32_t change){


}

static uint8_t  bestSeller(void){


}

static void     dayReport(void){


}