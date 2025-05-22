
/*
 * Copyright (C) 2025 Tec de Monterrey
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#ifndef ANALYSIS_H
#define ANALYSIS_H

#include <string>
#include <vector>
#include <utility>

/**
 * @brief Lee el contenido completo de un archivo de texto.
 *
 * @param filename Ruta del archivo.
 * @return Contenido del archivo como una cadena.
 */
std::string read_file_content(const std::string &filename);

/**
 * @brief Busca si un patrón existe dentro de un texto dado.
 *
 * @param text Texto completo donde se buscará.
 * @param pattern Patrón a buscar.
 * @return Par booleano e índice (1-based). True si se encuentra, junto con su posición.
 */
std::pair<bool, size_t> contains_pattern(const std::string &text, const std::string &pattern);

/**
 * @brief Encuentra el palíndromo más largo dentro del texto.
 *
 * @param text Texto a analizar.
 * @return Par con índice inicial y final del palíndromo (1-based).
 */
std::pair<int, int> longest_palindrome(const std::string &text);

/**
 * @brief Encuentra el substring común más largo entre dos textos.
 *
 * @param text1 Primer texto.
 * @param text2 Segundo texto.
 * @return Par con índice inicial y final del substring común (1-based).
 */
std::pair<int, int> longest_common_substring(const std::string &text1, const std::string &text2);

#endif // ANALYSIS_H
