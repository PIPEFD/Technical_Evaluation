# Threads - Prueba Técnica

This is a solution to thread concurrency using a random list of numbers sorted into two lists of positive and negative numbers.
Programa en C que genera números aleatorios usando múltiples threads y los clasifica en listas ordenadas (positivos/negativos).

## Compilación

```bash
make
```

## Uso

```bash
./threads <num_threads> <nums_per_thread> [opciones]
```

### Ejemplos

```bash
./threads 4 100        # 4 threads, 100 números cada uno

```

## Límites

- Threads: 1-1024
- Números por thread: 1-10,000,000

## Características

✓ Generación concurrente con pthread  
✓ Sincronización con mutex  
✓ Clasificación automática (pos/neg)  
✓ Ordenamiento con qsort  
✓ Sin memory leaks

## Implementación

### 🔢 Algoritmo RNG (xorshift64)

**Generación del número aleatorio**:
```c
unsigned long long rng_next(unsigned long long *state) {
    unsigned long long x = *state;
    x ^= x << 13;    // Mezcla: XOR con desplazamiento izquierdo
    x ^= x >> 7;     // Mezcla: XOR con desplazamiento derecho
    x ^= x << 17;    // Mezcla final
    *state = x;      // Actualizar estado
    return (int)x;   // Retornar como int (32 bits bajos)
}
```

**Por qué funciona**:
- Las operaciones XOR y shifts crean **avalanche effect**: un bit cambiado afecta muchos otros
- Período largo: ~2⁶⁴ números antes de repetirse
- Rápido: solo operaciones bitwise (sin multiplicaciones/divisiones)
- Determinista: misma seed → misma secuencia

**Inicialización por thread**:
```c
seed_global = PID ^ timestamp         // Seed base del proceso
rng_state = seed_global ^ thread_id   // Cada thread tiene estado único
```

### 🧵 Fórmulas Core

- **Seed única**: `seed = PID ^ timestamp ^ thread_id`
- **Memoria total**: `space = threads × nums_per_thread × sizeof(int)`
- **Distribución**: `index = (random < 0) ? NEGATIVE : POSITIVE`
**Memoria**: `M = 8 × T × K bytes` (listas) + `T × 8MB` (stacks)  

### ⚙️ Características Técnicas

- **2 listas compartidas** con mutexes independientes (reducción de contención)
- **Pre-asignación** de memoria calculada (sin reallocaciones dinámicas)
- **Cleanup completo** con destrucción de mutexes y liberación de recursos
- *Norma** (sin truncar).

## 🔬 Análisis de Correctitud

### Thread Safety
✓ **Sin deadlocks**: Solo un mutex por operación (no hay bloqueos anidados)  
✓ **Sin data races**: Todas las escrituras protegidas por mutex  
✓ **RNG thread-safe**: Cada thread tiene su propia seed (`global ^ thread_id`)


