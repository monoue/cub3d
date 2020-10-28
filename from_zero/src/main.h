


#define DEBUGV(v_fmt, v) \
    printf(#v ": " v_fmt "\t(file \"%s\", line %d, in %s)\n", \
        v, __FILE__, __LINE__, __FUNCTION__);

#define DEBUGVD(v) DEBUGV("%d", v);
#define DEBUGVS(v) DEBUGV("%s", v);

#define DEBUGF(fmt, ...) \
    printf(fmt "\t(file \"%s\", line %d, in %s)\n", \
        __VA_ARGS__, __FILE__, __LINE__, __FUNCTION__);



// typedef enum	e_ids
// {
// 	RESOLUTION,
// 	NORTH_TEXTURE,
// 	EAST_TEXTURE,
// 	WEST_TEXTURE,
// 	SOUTH_TEXTURE,
// 	SPRITE_TEXTURE,
// 	FLOOR_COLOR,
// 	CEILING_COLOR,

// 	ID_NUM
// }				t_ids;



// 切り分けて、t_mlx_data とかの方がいいかも？
