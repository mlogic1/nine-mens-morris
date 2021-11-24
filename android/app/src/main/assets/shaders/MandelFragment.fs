#version 300 es

precision highp float;

out vec4 FragColor;
in vec3 gl_FragCoord;

uniform float WINDOW_RESOLUTION_W;
uniform float WINDOW_RESOLUTION_H;

const float real_min = -2.0f;
const float real_max = 1.2f;
const float imag_min = -1.2f;
const float imag_max = 1.2f;

const int ITER_COUNT = 85;

struct ComplexNumber
{
    float real;
    float imag;
};

void main()
{
    // x
    float range_real = WINDOW_RESOLUTION_W;
    float input_x = (gl_FragCoord.x - 0.0f) / range_real;

    // scale to norm range
    float range2_x = real_max - real_min; 
    float normalized_x = (input_x * range2_x) + real_min;

    // y
    float range_imag = WINDOW_RESOLUTION_H;
    float input_y = (gl_FragCoord.y - 0.0f) / range_imag;

    // scale to norm range
    float range2_y = imag_max - imag_min;
    float normalized_y = (input_y * range2_y) + imag_min;

    ComplexNumber z;
    z.real = 0.0f;
    z.imag = 0.0f;

    ComplexNumber c;
    c.real = normalized_x;
    c.imag = normalized_y;

    // zoom?
    //c.real *= 0.65f;
    //c.imag *= 0.65f;

    bool outofBounds = false;
    float total_iterations = 0;
    for (int iter = 0 ; iter < ITER_COUNT ; ++iter)
    {
        // square
        float r = z.real;
        float i = z.imag;

        //z.real = ((r * r) - (i * i));
        //z.imag = ((r * i) + (i * r) );
        z.real = pow(r, 2) - pow(i, 2);
        z.imag = 2 * r * i;
        
        // add
        z.real += c.real;
        z.imag += c.imag;

        vec2 lmao = vec2(z.real, z.imag);
        float len = length(lmao);

        total_iterations = iter;
        if (len > 2.0f)
        {
            outofBounds = true;
            break;
        }
    }

    if (outofBounds)
    {
        total_iterations = total_iterations / ITER_COUNT;
        FragColor = vec4(total_iterations, 0.0f, 0.0f, 1.0f);
    }
    else
    {
        FragColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
    }
}