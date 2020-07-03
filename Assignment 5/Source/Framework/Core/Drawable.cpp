#include "Drawable.h"


namespace GameDev2D
{
    Drawable::Drawable() : Transformable(),
        m_Shader(nullptr),
        m_Color(Color::WhiteColor()),
        m_Anchor(0.0f, 0.0f),
		m_BlendingMode(BlendingMode())
    {

    }

    Drawable::~Drawable()
    {

    }

    Shader* Drawable::GetShader()
    {
        return m_Shader;
    }

    void Drawable::SetShader(Shader* aShader)
    {
        m_Shader = aShader;
    }

    Color Drawable::GetColor()
    {
        return m_Color;
    }

    void Drawable::SetColor(Color aColor)
    {
        m_Color = aColor;
    }

	float Drawable::GetAlpha()
	{
		return m_Color.a;
	}

	void Drawable::SetAlpha(float aAlpha)
	{
		Color color = m_Color;
		color.a = aAlpha;
		SetColor(color);
	}

    Vector2 Drawable::GetAnchor()
    {
        return m_Anchor;
    }

    void Drawable::SetAnchor(Vector2 aAnchor)
    {
        m_Anchor = aAnchor;
    }

	void Drawable::SetAnchor(float aAnchorX, float aAnchorY)
	{
		m_Anchor.x = aAnchorX;
		m_Anchor.y = aAnchorY;
	}

	void Drawable::SetAnchorX(float aAnchorX)
	{
		m_Anchor.x = aAnchorX;
	}

	void Drawable::SetAnchorY(float aAnchorY)
	{
		m_Anchor.y = aAnchorY;
	}

	void Drawable::SetBlendingMode(BlendingFactor aSource, BlendingFactor aDestination)
	{
		m_BlendingMode.source = aSource;
		m_BlendingMode.destination = aDestination;
	}

	void Drawable::SetBlendingMode(BlendingMode aBlendingMode)
	{
		m_BlendingMode = aBlendingMode;
	}

	BlendingMode Drawable::GetBlendingMode()
	{
		return m_BlendingMode;
	}
}