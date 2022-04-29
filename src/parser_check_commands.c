/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check_commands.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coverand <coverand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 17:55:09 by coverand          #+#    #+#             */
/*   Updated: 2022/04/29 18:28:29 by coverand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Error management:
1) If '>', '>>', '<', '<<' are the last args or there is no args b/w redirects:
"bash: syntax error near unexpected token `newline'"

2) If there is 2 pipes
"bash: syntax error near unexpected token `|'"

3) Just 1 arg - 1 pipe
bash: syntax error near unexpected token `|'

4) Unclosed quotes messages:
bash: syntax error: '"'
bash: syntax error: '"

5) export ARG = "5" -> There cannot be any space on either side of the equal sign.
bash: export: `=': not a valid identifier
bash: export: `5': not a valid identifier
*/