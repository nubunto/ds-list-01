#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student {
    char name[256];
    int number;
} Student;

typedef struct Course {
    char name[256];
    Student* students;
    int students_size;
} Course;

int Student_print(Student);
int Students_print(Student*, int);

int Course_init_students(Course*, int);
int Course_read_students(Course*);
int Course_print(Course*);

int get_dupl_students(Course*, Course*, Student*, int*);

int main() {
    Course *mdp = malloc(sizeof(Course));
    strcpy(mdp->name, "Métodos de Programação");
    Course_read_students(mdp);

    Course *ma = malloc(sizeof(Course));
    strcpy(ma->name, "Matemática Aplicada");
    Course_read_students(ma);

    Course_print(mdp);
    Course_print(ma);

    printf("Mostrando alunos matriculados em ambos os cursos...\n");
    // O maior número possível de alunos em ambos os cursos é o curso com maior número de alunos.
    int max_dupl_students = mdp->students_size > ma->students_size ? mdp->students_size : ma->students_size;
    Student *list_of_dupls = malloc(max_dupl_students * sizeof(Student));
    int number_of_students = 0;
    // get_dupl_students popula o vetor de estudantes, e também retorna o valor real de estudantes.
    get_dupl_students(mdp, ma, list_of_dupls, &number_of_students);

    Students_print(list_of_dupls, number_of_students);
}

int Course_init_students(Course *c, int size) {
    c->students = malloc(size * sizeof(Student));
    c->students_size = size;
}

int Course_read_students(Course *c) {
    printf("Digite o número de alunos que estão matriculados em '%s': ", c->name);
    int total_students = 0;
    scanf("%d", &total_students);
    Course_init_students(c, total_students);
    for (int i = 0; i < total_students; i++) {
        char name[256];
        printf("Digite o nome do aluno #%d de '%s': ", i + 1, c->name);
        scanf("%s", name);

        int number = 0;
        printf("Digite a matrícula do aluno #%d de '%s': ", i + 1, c->name);
        scanf("%d", &number);

        // Mais C99, por favor.
        Student st = {.number = number};
        strcpy(st.name, name);
        c->students[i] = st;
    }
}

int Course_print(Course *c) {
    printf("Course '%s'\n\n", c->name);
    printf("Students: \n");
    if (c->students_size == 0) {
        printf("No students.\n");
        return 0;
    }
    for (int i = 0; i < c->students_size; i++) {
        Student_print(c->students[i]);
    }
    printf("\n\n");
}

int Student_print(Student st) {
    printf("Student Name: %s\n", st.name);
    printf("Student Number: %d\n", st.number);
}

int Student_equal(Student a, Student b) {
    // Estudantes são iguais se seus nomes e números de matrícula são iguais.
    return strcmp(a.name, b.name) == 0 && a.number == b.number;
}

int get_dupl_students(Course *a, Course *b, Student *list_of_dupls, int *real_number_of_students) {
    // Vou assumir que o vetor list_of_dupls está vazio.
    int list_of_dupls_count = 0;

    for (int i = 0; i < a->students_size; i++) {
        Student student_a = a->students[i];
        for (int j = 0; j < b->students_size; j++) {
            Student student_b = b->students[j];
            if (Student_equal(student_a, student_b) == 1) {
                list_of_dupls[list_of_dupls_count++] = student_a;
            }
        }
    }
    *real_number_of_students = list_of_dupls_count;
}

int Students_print(Student *st, int size) {
    for (int i = 0; i < size; i++) {
        Student_print(st[i]);
    }
}