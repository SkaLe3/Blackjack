#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Core
{
	struct Transform
	{
		glm::vec3 Translation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 Rotation = { 0.0f, 0.0f, 0.0f }; /** In Radians, z - counterclockwise */
		glm::vec3 Scale = { 1.0f, 1.0f, 1.0f };

		Transform operator*(const Transform other) const
		{
			Transform result;
			result.Scale = Scale * other.Scale;
			result.Rotation = Rotation + other.Rotation;

			glm::vec3 scaledTranslation = other.Translation * Scale;
			glm::vec3 rotatedTranslation = glm::rotate(glm::mat4(1.0f), Rotation.z, glm::vec3(0, 0, 1)) * glm::vec4(scaledTranslation, 1.0f);
			result.Translation = Translation + glm::vec3(rotatedTranslation);
			return result;
		}

		glm::mat4 ToMat4()
		{
			return glm::translate(glm::mat4(1.0f), Translation)
				* glm::rotate(glm::mat4(1.0f), Rotation.z, glm::vec3(0, 0, 1))
				* glm::scale(glm::mat4(1.0f), Scale);
		}
	};
}