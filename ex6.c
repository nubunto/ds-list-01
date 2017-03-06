#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio_ext.h>

// número de questões da prova
#define TEST_QUESTIONS 5

// número de escolhas por questão (A, B, C, D, E)
#define CHOICES_NUM 2

typedef struct Choice {
    char text[256];
    int correct;
} Choice;

typedef struct Question {
    char text[256];
    Choice *choices;
} Question;

typedef struct Test {
    char name[128];
    Question *questions;
} Test;

typedef struct TestResults {
    int grade;
    int approved;
} TestResults;

typedef struct Student {
    char name[256];
    int number;
    char course[256];
    int *answers;
    TestResults *test_results;
} Student;

int Test_read(Test*);
int Test_read_questions(Test*);
int Test_print(Test*);

int Questions_print(Question*);

int Choices_read(Choice*);
int Choices_print(Choice*);

int Students_read(Student*, int);
int Student_read_answers(int*);
int Students_print(Student*, int);
int Student_print(Student);
int Student_print_answers(int*);

char choice_to_index(int);
int index_to_choice(char);

int correct_test(Test*, Student*, int);

int main() {
    Test *t = malloc(sizeof(Test));
    Test_read(t);

    printf("Resumo do seu gabarito: \n");
    Test_print(t);

    int students_num = 0;
    printf("Digite o número de alunos: ");
    scanf("%d", &students_num);
    Student *students = malloc(students_num * sizeof(Student));

    Students_read(students, students_num);
    printf("Resumo dos seus alunos: \n");

    Students_print(students, students_num);

    correct_test(t, students, students_num);
}

int Students_read(Student *students, int size) {
    for (int i = 0; i < size; i++) {
        char name[256];
        printf("Digite o nome do aluno #%d: ", i + 1);
        scanf("%s", name);

        char course[256];
        printf("Digite o nome do curso do aluno %s: ", name);
        scanf("%s", course);

        int number = 0;
        printf("Digite o numero da matricula do aluno %s: ", name);
        scanf("%d", &number);

        Student st = {.number = number};
        strcpy(st.name, name);
        strcpy(st.course, course);
        st.answers = malloc(TEST_QUESTIONS * sizeof(int));
        st.test_results = malloc(sizeof(TestResults));
        Student_read_answers(st.answers);

        students[i] = st;
    }
}

int Student_read_answers(int *answers) {
    for(int i = 0; i < TEST_QUESTIONS; i++) {
        printf("Digite a escolha desse aluno para a questão #%d: ", i + 1);
        char index;
        fflush(stdin);
        scanf(" %c", &index);
        printf("INDEX: %c   ", index);
        int transformed = index_to_choice(index);
        printf("INDEX_AFTER: %d\n", transformed);
        answers[i] = transformed;
    }
}

int Students_print(Student *students, int size) {
    for(int i = 0; i < size; i++) {
        printf("Aluno #%d\n", i + 1);
        Student_print(students[i]);
    }
}

int Student_print(Student st) {
    printf("Nome: %s\n", st.name);
    printf("Curso: %s\n", st.course);
    printf("Numero de matricula: %d\n", st.number);
    Student_print_answers(st.answers);
    printf("\n\n");
}

int Student_print_answers(int *answers) {
    for(int i = 0; i < TEST_QUESTIONS; i++) {
        printf("Resposta da questao #%d: ", i + 1);
        printf("%c", choice_to_index(answers[0]));
        printf("\n");
    }
}

int Test_read(Test *t) {
    char name[128];
    printf("Digite o nome da prova: ");
    scanf(" %s", name);
    strcpy(t->name, name);

    t->questions = malloc(TEST_QUESTIONS * sizeof(Question));
    Test_read_questions(t);
}

int Test_read_questions(Test *t) {
    for (int i = 0; i < TEST_QUESTIONS; i++) {
        Question q;

        char text[256];
        printf("Digite o texto da questão #%d: ", i + 1);
        scanf("%s", text);
        strcpy(q.text, text);

        q.choices = malloc(CHOICES_NUM * sizeof(Choice));
        Choices_read(q.choices);
        t->questions[i] = q;
    }
}

char choice_to_index(int i) {
    switch(i) {
        case 0: return 'A';
        case 1: return 'B';
        case 2: return 'C';
        case 3: return 'D';
        case 4: return 'E';
    }
}

int index_to_choice(char c) {
    switch(c) {
        case 'A': return 0;
        case 'B': return 1;
        case 'C': return 2;
        case 'D': return 3;
        case 'E': return 4;
    }
}

int Choices_read(Choice *choices) {
    int already_correct;
    for (int i = 0; i < CHOICES_NUM; i++) {
        char text[256];
        printf("Digite o texto da resposta %c: ", choice_to_index(i));
        scanf("%s", text);
        fflush(stdin);

        int correct = 0;
        printf("Esta questão é a correta (y/n) ?");
        char correct_chr;
        scanf(" %c", &correct_chr);
        if (correct_chr == 'y') {
            correct = 1;
        }

        Choice c = {.correct = correct};
        strcpy(c.text, text);
        choices[i] = c;
    }
}

int Test_print(Test *t) {
    printf("Nome da prova: %s\n", t->name);
    Questions_print(t->questions);
}

int Questions_print(Question *questions) {
    for(int i = 0; i < TEST_QUESTIONS; i++) {
        Question q = questions[i];

        printf("Pergunta #%d: %s\n", i+1, q.text);
        Choices_print(q.choices);
    }
}

int Choices_print(Choice *choices) {
    for(int i = 0; i < CHOICES_NUM; i++) {
        Choice c = choices[i];
        printf("\t%c) %s", choice_to_index(i), c.text);
        if(c.correct) {
            printf("[correta]");
        }
        printf("\n");
    }
}

int correct_test(Test *t, Student *students, int size) {
    for(int i = 0; i < TEST_QUESTIONS; i++) {
        Question q = t->questions[i];
        for(int j = 0; j < size; j++) {
            Student st = students[i];
            int grade = 0;
            for(int k = 0; k < CHOICES_NUM; k++) {
                int answer_index = st.answers[k];
                Choice c = q.choices[answer_index];
                if(c.correct) {
                    grade++;
                }
            }
            st.test_results->grade = grade;
            // só realmente fica igual ao enunciado se TEST_QUESTIONS == 10.
            st.test_results->approved = (grade/2) >= (TEST_QUESTIONS/2) ? 1 : 0;
        }
    }
    float approval_sum = 0;
    for(int i = 0; i < size; i++) {
        Student st = students[i];
        if(st.test_results->approved) {
            approval_sum++;
            printf("Estudante %s, matricula nº %d, foi aprovado (%d)\n", st.name, st.number, st.test_results->grade);
        } else {
            printf("Estudante %s, matricula nº %d, NÃO foi aprovado (%d)\n", st.name, st.number, st.test_results->grade);
        }
    }
    printf("Taxa de aprovação: %.2f%%\n", (approval_sum/size) * 100);
}