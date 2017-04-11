/**
 * Created by lvHiei on 17-4-11.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageLuminanceThresholdFilter.h"


// 片元着色器
const char _luminanceThreshold_fragment_shader[]=
"precision mediump float;\n"
"varying vec2 textureCoordinate;\n"
"\n"
"uniform sampler2D inputImageTexture;\n"
"uniform float threshold;\n"
"\n"
"const vec3 W = vec3(0.2125, 0.7154, 0.0721);\n"
"\n"
"void main()\n"
"{\n"
"    vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);\n"
"    float luminance = dot(textureColor.rgb, W);\n"
"    float thresholdResult = step(threshold, luminance);\n"
"\n"
"    gl_FragColor = vec4(vec3(thresholdResult), textureColor.w);\n"
"}"
;


GPUImageLuminanceThresholdFilter::GPUImageLuminanceThresholdFilter()
    : GPUImageFilter(_luminanceThreshold_fragment_shader)
{
    m_fThreshold = 0.5f;
    m_iThresholdUniformLocation = -1;
}

GPUImageLuminanceThresholdFilter::~GPUImageLuminanceThresholdFilter()
{

}

void GPUImageLuminanceThresholdFilter::setThreshold(float threshold)
{
    m_fThreshold = threshold;
}

void GPUImageLuminanceThresholdFilter::setThreshold(int percent)
{
    if(percent < 0){
        percent = 0;
    }

    if(percent > 100){
        percent = 100;
    }

    float incremental = (1.0f - 0.0f) / 100;

    m_fThreshold = 0.0f + incremental * percent;
}

bool GPUImageLuminanceThresholdFilter::createProgramExtra()
{
    m_iThresholdUniformLocation = glGetUniformLocation(m_uProgram, "threshold");
    return GPUImageFilter::createProgramExtra();
}

bool GPUImageLuminanceThresholdFilter::beforeDrawExtra()
{
    glUniform1f(m_iThresholdUniformLocation, m_fThreshold);
    return GPUImageFilter::beforeDrawExtra();
}
