#ifndef COLLISION_HEADER
#define COLLISION_HEADER

class Collision {
public:
    static bool WindowCollision (const float &cx1, const float &cy1,
                                 const float &minHeight, const float &minWidth,
                                 const float &maxHeight, const float &maxWidth) {

                                     if (cx1 < minWidth)
                                        return true;

                                     if (cx1 > maxWidth)
                                        return true;

                                     if (cy1 < minHeight)
                                        return true;

                                     if (cy1 > maxHeight)
                                        return true;

                                     return false;
    }

    static bool WindowCircleCollisionB (const float &cr1, const float &cx1, const float &cy1,
                                       const float &minHeight, const float &minWidth,
                                       const float &maxHeight, const float &maxWidth) {

                                        if (cx1 + cr1 < minWidth)
                                            return true;

                                        if (cx1 - cr1 > maxWidth)
                                            return true;

                                        if (cy1 + cr1 < minHeight)
                                            return true;

                                        if (cy1 - cr1 > maxHeight)
                                            return true;

                                        return false;
    }

    static std::string WindowCircleCollisionS (const float &cr1, const float &cx1, const float &cy1,
                                               const float &minHeight, const float &minWidth,
                                               const float &maxHeight, const float &maxWidth) {


                                        if (cx1 + cr1 < minWidth)
                                            return "Left";

                                        if (cx1 - cr1 > maxWidth)
                                            return "Right";

                                        if (cy1 + cr1 < minHeight)
                                            return "Up";

                                        if (cy1 - cr1 > maxHeight)
                                            return "Down";

                                        return "null";



                                               }



};



#endif // COLLISION_HEADER
