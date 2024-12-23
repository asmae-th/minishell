/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleeeerr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmae <asmae@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 10:29:10 by asmae             #+#    #+#             */
/*   Updated: 2024/12/22 15:13:32 by asmae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdlib.h>
// #include <string.h>
// #include <stdio.h>

// // Définition des structures
// typedef enum e_token_type {
//     WORD,
//     OPERATOR,
//     REDIRECTION
// } t_token_type;

// typedef enum e_token_state {
//     NORMAL,
//     IN_SQUOT,
//     IN_DQUOT
// } t_token_state;

// typedef struct token_list {
//     char *token;
//     t_token_type type;
//     t_token_state state;
//     int index;
//     int node_member;
//     struct token_list *next;
//     struct token_list *prev;
// } t_token;

// typedef struct start_end_geter {
//     int start;
//     int end;
//     int flag;
//     int node_member;
// } t_pos_get;


// 7. Libère une région de la liste
void free_region(t_token **start, t_token **end) {
    t_token *current = *start;
    t_token *next;

    while (current && current != *end) {
        next = current->next;
        free(current->token);
        free(current);
        current = next;
    }

    if (current) { // Libère le noeud de fin
        free(current->token);
        free(current);
    }

    *start = NULL;
    *end = NULL;
}

// 1. Supprime les guillemets d'un token
char *token_withoutquote(char *token, t_token_state state) {
    char *result;
    int len = strlen(token), i = 0, j = 0;

    // Alloue de la mémoire pour la chaîne nettoyée
    result = (char *)malloc(len + 1);
    if (!result)
        return NULL;

    while (token[i]) {
        if ((state == IN_SQUOT && token[i] != '\'') ||
            (state == IN_DQUOT && token[i] != '\"') ||
            (state == NORMAL)) {
            result[j++] = token[i];
        }
        i++;
    }

    result[j] = '\0'; // Termine la chaîne
    return result;
}

// 2. Trouve la plage d'index à traiter
t_pos_get *index_range_getter(t_token **tokens) {
    t_pos_get *pos = (t_pos_get *)malloc(sizeof(t_pos_get));
    t_token *current = *tokens;

    if (!pos)
        return NULL;

    pos->start = -1;
    pos->end = -1;
    pos->flag = 0;
    pos->node_member = 0;

    while (current) {
        if (current->state == IN_SQUOT || current->state == IN_DQUOT) {
            if (pos->start == -1)
                pos->start = current->index;
            pos->end = current->index;
            pos->node_member++;
        }
        current = current->next;
    }

    return pos;
}

// 3. Retourne l'état réel du token
int true_state(t_token *current) {
    if (!current)
        return NORMAL;
    if (current->state == IN_SQUOT || current->state == IN_DQUOT)
        return current->state;
    return NORMAL;
}

// 4. Ajoute un noeud nettoyé dans la liste
void addclean_token(t_token **head, int start_index, int end_index, t_token *clean_node) {
    t_token *current = *head;
    t_token *start = NULL, *end = NULL;

    // Trouve les noeuds de début et de fin
    while (current) {
        if (current->index == start_index)
            start = current;
        if (current->index == end_index)
            end = current;
        current = current->next;
    }

    if (start && end) {
        clean_node->next = end->next;
        clean_node->prev = start->prev;

        if (start->prev)
            start->prev->next = clean_node;
        if (end->next)
            end->next->prev = clean_node;

        // Libère la mémoire des noeuds entre start et end
        free_region(&start, &end);
    }
}

// 5. Concatène les tokens dans une plage
t_token *data_assembler(t_token **tokens, t_pos_get *position) {
    t_token *current = *tokens;
    t_token *new_node = (t_token *)malloc(sizeof(t_token));
    char *assembled_data = NULL;

    if (!new_node)
        return NULL;

    assembled_data = strdup("");

    while (current) {
        if (current->index >= position->start && current->index <= position->end) {
            char *temp = assembled_data;
            assembled_data = strcat(strdup(assembled_data), current->token);
            free(temp);
        }
        current = current->next;
    }

    new_node->token = assembled_data;
    new_node->type = WORD;
    new_node->state = NORMAL;
    new_node->index = position->start;
    new_node->node_member = position->node_member;
    new_node->next = NULL;
    new_node->prev = NULL;

    return new_node;
}

// 6. Gère des cas particuliers
// void specialcase_handler(t_token **tokens)
// {
//     t_token *current = *tokens;

//     while (current) {
//         if (current->state == NORMAL && strcmp(current->token, "") == 0) {
//             // Supprime les tokens vides
//             t_token *to_free = current;
//             if (current->prev)
//                 current->prev->next = current->next;
//             if (current->next)
//                 current->next->prev = current->prev;
//             current = current->next;
//             free(to_free->token);
//             free(to_free);
//         } else {
//             current = current->next;
//         }
//     }
// }

