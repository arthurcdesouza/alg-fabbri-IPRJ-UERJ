#define TEST_MODE
#include <gtest/gtest.h>

extern "C" {
    #include "../dynagraph.c"
}

class DynagraphTest : public ::testing::Test {
protected:
    no nos[5];
    const char *nomes[5] = {"Petropolis", "Teresopolis", "Niteroi", "Rio", "Friburgo"};

    void SetUp() override {
        for (int i = 0; i < 5; ++i) {
            strcpy(nos[i].nome, nomes[i]);
            nos[i].conexoes = NULL;
        }

        liga(nos+0, nos+1, 50); // Petropolis - Teresopolis
        liga(nos+0, nos+3, 65); // Petropolis - Rio
        liga(nos+1, nos+3, 100); // Teresopolis - Rio
        liga(nos+1, nos+4, 75); // Teresopolis - Friburgo
        liga(nos+2, nos+3, 15); // Niteroi - Rio
        liga(nos+2, nos+4, 120); // Niteroi - Friburgo
        liga(nos+3, nos+4, 140); // Rio - Friburgo
    }

    void TearDown() override {
        for (int i = 0; i < 5; ++i) {
            lista_ptr l = nos[i].conexoes;
            while (l) {
                lista_ptr next = l->next;
                free(l);
                l = next;
            }
        }
    }
};

TEST_F(DynagraphTest, DeletaNo) {
    // Node to delete is nos[3] ("Rio")
    deleta_no_grafo(nos+3);

    // Check that Rio's connections are gone
    ASSERT_EQ(nos[3].conexoes, nullptr);

    // Check that connections to Rio from other nodes are gone
    for (int i = 0; i < 5; ++i) {
        if (i == 3) continue; // Skip Rio itself

        lista_ptr l = nos[i].conexoes;
        while (l) {
            ASSERT_NE(l->no, nos+3);
            l = l->next;
        }
    }
}
