/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsap <gsap@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 09:30:19 by gsap              #+#    #+#             */
/*   Updated: 2022/01/22 15:07:30 by gsap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
  char *inpt;

  inpt = "";
  while (inpt)
  {
    inpt = readline("> ");
    if (ft_strncmp(inpt, "exit", 5) == 0)
      break;
    add_history(inpt);
    printf("%s\n", inpt);
    free(inpt);
  }
  return (0);
}
