#pragma once


namespace GameDev2D
{
	class Timer
	{
	public:
		Timer(double duration);

		void Update(double delta);

		void Start();
		void Stop();

		void Reset();   //Resets a timer back to zero but doesn't start it
		void Restart(); //Resets AND Starts the timer

		double GetDuration();
		double GetElapsed();
		double GetRemaining();

		float GetPercentageComplete();

		void SetDoesRepeat(bool doesRepeat);
		bool GetDoesRepeat();

		bool IsRunning();
		bool IsDone();

	private:
		double m_Duration;
		double m_Elapsed;
		bool m_IsRunning;
		bool m_DoesRepeat;
	};
}