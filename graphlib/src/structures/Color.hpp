#ifndef GL_COLOR_HPP
#define GL_COLOR_HPP

#include <cmath>

#define GL_FORCE_INTO_RANGE(VAR,LOWER,UPPER) \
VAR < LOWER ? LOWER : (VAR > UPPER ? UPPER : VAR)

namespace gl {
  
/**
 * @class Color
 * @brief Stores an RGBA Color.
 */
class Color {
public:
  using color_val_t = unsigned char;

  /**
   * @name Constructs
   * @brief Constructs a new Color object.
   */
  //@{
  /**
   * @brief Default constructor.
   */
  Color () = default;
  /**
   * @brief Constructor for integer R,G,B,A values.
   * @param[in] r R value. \f$r \in \{0,...,255\}\f$
   * @param[in] g G value. \f$g \in \{0,...,255\}\f$
   * @param[in] b B value. \f$b \in \{0,...,255\}\f$
   * @param[in] a Alpha value. \f$a \in \{0,...,100\}\f$
   */
  Color (const int r, const int g,
         const int b, const int a = 100) :
         r_(static_cast<color_val_t>(GL_FORCE_INTO_RANGE(r,0,255))), 
         g_(static_cast<color_val_t>(GL_FORCE_INTO_RANGE(g,0,255))), 
         b_(static_cast<color_val_t>(GL_FORCE_INTO_RANGE(b,0,255))), 
         a_(static_cast<color_val_t>(GL_FORCE_INTO_RANGE(a,0,100))) {}
  /**
   * @brief Constructor for separate float R,G,B,A values.
   * @param[in] r R value. \f$r \in [0,1]\f$
   * @param[in] g G value. \f$g \in [0,1]\f$
   * @param[in] b B value. \f$b \in [0,1]\f$
   * @param[in] a Alpha value. \f$a \in [0,1]\f$
   */
  Color (const double r, const double g,
         const double b, const double a = 1.0) :
         r_(static_cast<color_val_t>(GL_FORCE_INTO_RANGE(r,0.,1.)*255)),
         g_(static_cast<color_val_t>(GL_FORCE_INTO_RANGE(g,0.,1.)*255)), 
         b_(static_cast<color_val_t>(GL_FORCE_INTO_RANGE(b,0.,1.)*255)), 
         a_(static_cast<color_val_t>(GL_FORCE_INTO_RANGE(a,0.,1.)*100)) {}
  /**
   * @brief Constructor for combined hexadecimal R,G,B,A values.
   * @param[in] hex Hexadecimal color code. Format: \f$ 0xAARRGGBB \f$ where \f$ RR, GG, BB \f$ signify the red, blue and green bytes. \f$ AA \f$ is optional and signifies the alpha (opacity) byte.
   */
  Color (const unsigned int hex) : a_(0x64),
  r_((hex >> 16) & 0xFF),
  g_((hex >> 8) & 0xFF),
  b_((hex) & 0xFF) {
    if ((hex >> 24) > 0) {
      const color_val_t a = (hex >> 24) & 0xFF;
      a_ = a > 0x64 ? 0x64 : a;
    }
  }
  //@}

   Color(Color &&) noexcept = default;
   Color &operator=(const Color &) = default;
   Color &operator=(Color &&) noexcept = default;
  ~Color () = default;
  /**
   * @name Read access to stored RGBA color values.
   * @brief Getters for stored color values.
   */
  //@{
  /**
   * @brief Gets the hexadecimal value of the RGBA color.
   */
  int hex() const { 
    return (a_ << 24) | (r_ << 16) | (g_ << 8) | b_;
    }
  /**
   * @brief Gets the R-value of the RGBA color.
   */
  color_val_t r() const { return r_; }
  /**
   * @brief Gets the G-value of the RGBA color.
   */
  color_val_t g() const { return g_; }
  /**
   * @brief Gets the B-value of the RGBA color.
   */
  color_val_t b() const { return b_; }
  /**
   * @brief Gets the Alpha-value of the RGBA color.
   */
  color_val_t a() const { return a_; }
  //@}

  /**
   * @name Write access to stored RGBA color values.
   * @brief Setters for stored color values
   * Tâkes the new value for the red/blue/green/alpha respectively.
   */
  //@{
  /**
   * @brief Sets all values of the RGBA color.
   * @param[in] hex Input hexadecimal color code. 
   */
  void hex (const int hex) { 
    r_ = (hex >> 16) & 0xFF;
    g_ = (hex >> 8) & 0xFF;
    b_ = (hex) & 0xFF;
    if ((hex >> 24) > 0) {
      const color_val_t a = (hex >> 24) & 0xFF;
      a_ = a > 0x64 ? 0x64 : a;
    }
   }
  /**
   * @brief Sets the R-value of the RGBA color.
   */
  void r (color_val_t r) { r_ = r; }
  /**
   * @brief Sets the G-value of the RGBA color.
   */
  void g (color_val_t g) { g_ = g; }
  /**
   * @brief Sets the B-value of the RGBA color.
   */
  void b (color_val_t b) { b_ = b; }
  /**
   * @brief Sets the Alpha-value of the RGBA color.
   */
  void a (color_val_t a) { a_ = a; }
  //@}

private:
  color_val_t r_, /**< 
                   * @brief Red value. \f$r \in \{0,...,255\}\f$
                   */
              g_,  /**< 
                   * @brief Green value.  \f$g \in \{0,...,255\}\f$
                   */
              b_,  /**< 
                   * @brief Blue value. \f$b \in \{0,...,255\}\f$
                   */
              a_;  /**< 
                   * @brief Alpha (opacity) value. \f$a \in \{0,...,100\}\f$
                   */
};

} // namespace gl

#endif // GL_COLOR_HPP