
class congfx : public snakegfx
{
public:
	/* initialize gfx */
	void init();
	/* render the whole field. override me */
	void renderplane(snakeplane* sp, snake* s);

	/* rotate the cube: 1=down, 2=up, 3=left, 4=right */
	void rotatecube(int dir);

	/* constructor */
	congfx();
	/* destructor */
	virtual ~congfx();
};
