#ifndef GL_COLOR_HPP
#define GL_COLOR_HPP

#include <cmath>
#include <unordered_map>
#include <string>
#include <functional>
#include <sstream>
#include <iomanip>

#define GL_FORCE_INTO_RANGE(VAR, LOWER, UPPER) \
  VAR < LOWER ? LOWER : (VAR > UPPER ? UPPER : VAR)

namespace gl
{

/**
 * @class Color
 * @brief Stores an RGBA Color.
 */
class Color
{
public:
  using color_val_t = unsigned char; /**< color value type, has a range of exactly\f$ \{0,\ldots,255\}\f$ */

  /**
   * @name Constructors
   * @brief Constructs a new Color object.
   */
  //@{
  /**
   * @brief Default constructor.
   */
  Color() = default;
  /**
   * @brief Constructor for integer R,G,B,A values.
   * @param[in] r R value. \f$r \in \{0,\ldots,255\}\f$
   * @param[in] g G value. \f$g \in \{0,\ldots,255\}\f$
   * @param[in] b B value. \f$b \in \{0,\ldots,255\}\f$
   * @param[in] a Alpha value. \f$a \in \{0,\ldots,100\}\f$
   */
  Color(const int r, const int g,
        const int b, const int a = 100) : r_(static_cast<color_val_t>(GL_FORCE_INTO_RANGE(r, 0, 255))),
                                          g_(static_cast<color_val_t>(GL_FORCE_INTO_RANGE(g, 0, 255))),
                                          b_(static_cast<color_val_t>(GL_FORCE_INTO_RANGE(b, 0, 255))),
                                          a_(static_cast<color_val_t>(GL_FORCE_INTO_RANGE(a, 0, 100))) {}
  /**
   * @brief Constructor for separate double R,G,B,A values.
   * @param[in] r R value. \f$r \in [0,1]\f$
   * @param[in] g G value. \f$g \in [0,1]\f$
   * @param[in] b B value. \f$b \in [0,1]\f$
   * @param[in] a Alpha value. \f$a \in [0,1]\f$
   */
  Color(const double r, const double g,
        const double b, const double a = 1.0) : r_(static_cast<color_val_t>(GL_FORCE_INTO_RANGE(r, 0., 1.) * 255)),
                                                g_(static_cast<color_val_t>(GL_FORCE_INTO_RANGE(g, 0., 1.) * 255)),
                                                b_(static_cast<color_val_t>(GL_FORCE_INTO_RANGE(b, 0., 1.) * 255)),
                                                a_(static_cast<color_val_t>(GL_FORCE_INTO_RANGE(a, 0., 1.) * 100)) {}
  /**
   * @brief Constructor for combined hexadecimal R,G,B,A values.
   * @param[in] hex Hexadecimal color code. Format: \f$ 0xAARRGGBB \f$ where \f$ RR, GG, BB \f$ signify the red, blue and green bytes. \f$ AA \f$ is optional and signifies the alpha (opacity) byte.
   */
  Color(const unsigned int hex) : a_(0x64),
                                  r_((hex >> 16) & 0xFF),
                                  g_((hex >> 8) & 0xFF),
                                  b_((hex)&0xFF)
  {
    if ((hex >> 24) > 0)
    {
      const color_val_t a = (hex >> 24) & 0xFF;
      a_ = a > 0x64 ? 0x64 : a;
    }
  }
  /**
   * @brief Constructor for combined hexadecimal R,G,B,A values.
   * @param[in] name Name of color. Available are the following: \f$
   * \{"black","gray","silver","white","orange","maroon",\\"red","olive","yellow","green","lime","teal",\\"aqua", "navy","blue","purple","fuchsia"\}\f$
   * @param[in] a (optional) Opacity of the color. \f$ a\in\{0,\ldots,100\} \f$
   */
  Color(const char *name, color_val_t a = 100) : a_(a)
  {
    const std::unordered_map<std::string, std::function<void()>> map{
        {"black", [&]() { hex(0x000000); }},
        {"gray", [&]() { hex(0x808080); }},
        {"silver", [&]() { hex(0xC0C0C0); }},
        {"white", [&]() { hex(0xFFFFFF); }},
        {"orange", [&]() { hex(0xED9121); }},
        {"maroon", [&]() { hex(0x800000); }},
        {"red", [&]() { hex(0xFF0000); }},
        {"olive", [&]() { hex(0x808000); }},
        {"yellow", [&]() { hex(0xFFFF00); }},
        {"green", [&]() { hex(0x008000); }},
        {"lime", [&]() { hex(0x00FF00); }},
        {"teal", [&]() { hex(0x008080); }},
        {"aqua", [&]() { hex(0x00FFFF); }},
        {"navy", [&]() { hex(0x000080); }},
        {"blue", [&]() { hex(0x0000FF); }},
        {"purple", [&]() { hex(0x800080); }},
        {"fuchsia", [&]() { hex(0xFF00FF); }},
    };
    auto it = map.find(name);
    if (it != map.end())
    {
      it->second();
    }
    else
    {
      hex(0x000000);
    }
  }
  //@}
  Color(const Color &) = default;                ///< @brief Copy constructor
  Color(Color &&) noexcept = default;            ///< @brief Move constructor
  Color &operator=(const Color &) = default;     ///< @brief Copy assignment
  Color &operator=(Color &&) noexcept = default; ///< @brief Move assignment
  ~Color() = default;                            ///< @brief Destructor
  /**
   * @name Read access to stored RGBA color values.
   * @brief Getters for stored color values.
   */
  //@{
  /**
   * @brief Gets the hexadecimal value of the RGBA color as a string.
   */
  inline std::string RGBA() const
  {
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(8) << std::hex << (hex() | 0);
    return ss.str();
  }
  /**
   * @brief Gets the hexadecimal value of the RGB color as a string.
   */
  inline std::string RGB() const
  {
    std::stringstream ss;
    int val = (hex() >> 8) & 0xffffff;
    ss << std::setfill('0') << std::setw(6) << std::hex << (val | 0);
    return ss.str();
  }
  /**
   * @brief Gets the hexadecimal value of the RGBA color.
   */
  inline int hex() const
  {
    return (r_ << 24) | (g_ << 16) | (b_ << 8) | a_;
  }
  /**
   * @brief Gets the red value of the RGBA color.
   */
  inline color_val_t r() const { return r_; }
  /**
   * @brief Gets the green value of the RGBA color.
   */
  inline color_val_t g() const { return g_; }
  /**
   * @brief Gets the blue value of the RGBA color.
   */
  inline color_val_t b() const { return b_; }
  /**
   * @brief Gets the alpha/opacity value of the RGBA color.
   */
  inline color_val_t a() const { return a_; }
  //@}

  /**
   * @name Write access to stored RGBA color values.
   * @brief Setters for stored color values
   * Takes the new value for the red/blue/green/alpha respectively.
   */
  //@{
  /**
   * @brief Sets all values of the RGBA color.
   * @param[in] hex Input hexadecimal color code. 
   */
  inline void hex(const int hex)
  {
    r_ = (hex >> 16) & 0xFF;
    g_ = (hex >> 8) & 0xFF;
    b_ = (hex)&0xFF;
    if ((hex >> 24) > 0)
    {
      const color_val_t a = (hex >> 24) & 0xFF;
      a_ = a > 0x64 ? 0x64 : a;
    }
  }
  /**
   * @brief Sets the red value of the RGBA color.
   */
  inline void r(color_val_t r) { r_ = r; }
  /**
   * @brief Sets the green value of the RGBA color.
   */
  inline void g(color_val_t g) { g_ = g; }
  /**
   * @brief Sets the blue value of the RGBA color.
   */
  inline void b(color_val_t b) { b_ = b; }
  /**
   * @brief Sets the alpha/opacity value of the RGBA color.
   */
  inline void a(color_val_t a) { a_ = a; }
  //@}

private:
  color_val_t r_, ///< @brief Red value. \f$r \in \{0,\ldots,255\}\f$
              g_, ///< @brief Green value.  \f$g \in \{0,\ldots,255\}\f$
              b_, ///< @brief Blue value. \f$b \in \{0,\ldots,255\}\f$
              a_; ///< @brief Alpha/opacity value. \f$a \in \{0,\ldots,100\}\f$
};

} // namespace gl

#undef GL_FORCE_INTO_RANGE

#endif // GL_COLOR_HPP